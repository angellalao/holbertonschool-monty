#include "monty.h"

data_t *g_var;

/**
 * main - a program to interpret monty files
 * @argc: integer
 * @argv: array of strings
 *
 * Return: 0 if successful, or 1 for error
 */
int main(int argc, char *argv[])
{
	FILE *fp;
	char *opcode = NULL;
	unsigned int line_number = 0;
	size_t n = 0;
	ssize_t bytes_read;
	char *buffer = NULL;
	stack_t *stack;

	set_g_var_memory();
	g_var->arg = 0;
	printf("global_argument->argument: %d\n", g_var->arg);
	stack = NULL;
	check_arguments(argc);
	fp = x_fopen(argv[1]);
	bytes_read = getline(&buffer, &n, fp);
	line_number = 1;
	while (bytes_read >= 0)
	{
		opcode = get_opcode(buffer, line_number);
		if (opcode != NULL)
		{
			get_op_func(opcode)(&stack, line_number);
			free(opcode);
		}
		//free(buffer); - pretty sure we need to free -  but causes an error!
		line_number = line_number + 1;
		bytes_read = getline(&buffer, &n, fp);
	}
	free(buffer);
	fclose(fp);
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
	return;
}

/**
 * x_open - short description
 * @filename: a char *data type variable
 *
 * Return: type is int
 */

FILE *x_fopen(char *filename)
{
	FILE *fp;;

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

char *get_opcode(char *text_line, unsigned int line_number)
{
	char *return_value;
	char *token;
	char *delimeter = " \t\n";

	g_var->arg = 0;
	token = strtok(text_line, delimeter);
	if (token == NULL)
	{
		return (NULL);
	}
	return_value = strdup(token);
	if (strcmp(token, "push") == 0)
	{
		token = strtok(NULL, delimeter);
		if (token == NULL || check_digit(token) == 0)
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
		g_var->arg = atoi(token);
	}
	printf("return value: %s / global_arg: %d\n", return_value, g_var->arg);
	return (return_value);
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
	return print_error;
}

/**
 * print_error - print error message
 * @stack: double pointer to head of doubly linked list stack
 * @line_number: unsigned integer
 *
 * Return: void
 */
void print_error(__attribute__((unused)) stack_t **stack, unsigned int line_number)
{
	fprintf(stderr, "L%u: unknown instruction <opcode>\n", line_number);
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

	printf("sizeof stack_t: %ld\n", sizeof(stack_t));
	newNode = malloc(sizeof(*newNode));
	if (newNode == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	newNode->n = g_var->arg;
	newNode->prev = NULL;
	newNode->next = *stack;
	if (*stack != NULL)
	{
		(*stack)->prev = newNode;
	}
	*stack = newNode;
	printf("function to push integer %d to stack\n", g_var->arg);
}

int check_digit(char *str)
{
	int i;

	i = 0;
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

void print_all(__attribute__((unused)) stack_t **stack, __attribute__((unused)) unsigned int line_number)
{
	printf("function to print all data in the stack\n");
}

/**
 * initialise_global_variable - short description
 *
 * Return: type is void
 */

void set_g_var_memory()
{
	g_var = malloc(sizeof(*g_var));
	if (g_var == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
}
