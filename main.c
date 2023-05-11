#include "monty.h"

/**
 * main - a program to interpret monty files
 * @argc: integer
 * @argv: array of strings
 *
 * Return: 0 if successful, or 1 for error
 */
int main(int argc, char *argv[])
{
	unsigned int line_number;
	size_t n = 0;
	ssize_t bytes_read;
	char *buffer = NULL;
	stack_t *stack;

	stack = NULL;
	check_arguments(argc);
	g_var.fp = x_fopen(argv[1]);
	bytes_read = getline(&buffer, &n, g_var.fp);
	line_number = 1;
	while (bytes_read >= 0)
	{
		get_opcode(buffer, line_number, stack);
		free(buffer);
		if (g_var.opcode != NULL)
		{
			get_op_func(g_var.opcode)(&stack, line_number);
			free(g_var.opcode);
		}
		buffer = NULL;
		n = 0;
		line_number = line_number + 1;
		bytes_read = getline(&buffer, &n, g_var.fp);
	}
	free(buffer);
	free_stacklist(stack);
	fclose(g_var.fp);
	return (0);
}

/**
 * check_arguments - short description
 * @argc: a int data type variable
 *
 * Return: type is void
 */

void check_arguments(int argc)
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * x_open - short description
 * @filename: a char *data type variable
 *
 * Return: type is int
 */

FILE *x_fopen(char *filename)
{
	FILE *fp;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	return (fp);
}

/**
 * get_opcode - short description
 * @text_line: a char *data type variable
 *
 * Return: type is char *
 */

char *get_opcode(char *text_line, unsigned int line_number, stack_t *stack)
{
	char *token;
	char *delimeter = " \t\n";

	g_var.arg = 0;
	token = strtok(text_line, delimeter);
	if (token == NULL)
	{
		g_var.opcode = NULL;
		return (NULL);
	}
	g_var.opcode = strdup(token);
	if (strcmp(token, "push") == 0)
	{
		token = strtok(NULL, delimeter);
		if (token == NULL || check_digit(token) == 0)
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			free(text_line);
			free(g_var.opcode);
			fclose(g_var.fp);
			free_stacklist(stack);
			exit(EXIT_FAILURE);
		}
		g_var.arg = atoi(token);
	}
	return (g_var.opcode);
}

/**
 * get_op_func - pointer to a function that will match the opcode
 * @str: opcode
 *
 * Return: void
 */

void (*get_op_func(char *str))(stack_t **, unsigned int)
{
	instruction_t ops[] = {
		{"push", push_func},
		{"pall", print_all},
		{"pint", pint_func},
		{"pop", pop_func},
		{"swap", swap_func},
		{NULL, NULL}
	};
	int i;

	i = 0;
	while (ops[i].opcode != NULL)
	{
		if (strcmp(ops[i].opcode, str) == 0)
		{
			return (ops[i].f);
		}
		i = i + 1;
	}
	return (print_error);
}

/**
 * print_error - print error message
 * @stack: double pointer to head of doubly linked list stack
 * @line_number: unsigned integer
 *
 * Return: void
 */
void print_error(stack_t **stack, unsigned int line_number)
{
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, g_var.opcode);
	free(g_var.opcode);
	fclose(g_var.fp);
	free_stacklist(*stack);
	exit(EXIT_FAILURE);
}

/**
 * push_func - short description
 * @stack: a stack_t **data type variable
 * @line_number: a unsigned int data type variable
 *
 * Return: type is void
 */

void push_func(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	stack_t *newNode;

	newNode = malloc(sizeof(*newNode));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	newNode->n = g_var.arg;
	newNode->prev = NULL;
	newNode->next = *stack;
	if (*stack != NULL)
	{
		(*stack)->prev = newNode;
	}
	*stack = newNode;
}

/**
 * check_digit - short description
 * @str: a char *data type variable
 *
 * Return: 1 if string is made of digits, 0 if not
 */
int check_digit(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
	{
		i = 1;
	}
	while (str[i] != '\0')
	{
		if (isdigit(str[i]) == 0)
		{
			return (0);
		}
		i = i + 1;
	}
	return (1);
}

/**
 * print_all - short description
 * @stack: a stack_t **data type variable
 * @line_number: a unsigned int data type variable
 *
 * Return: type is void
 */

void print_all(stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		return;
	}
	temp = *stack;
	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * free_stacklist - short description
 * @head: a stack_t *data type variable
 *
 * Return: type is void
 */

void free_stacklist(stack_t *head)
{
	stack_t *temp;
	stack_t *current;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}
