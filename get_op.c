#include "monty.h"

/**
 * get_opcode - short description
 * @text_line: a char *data type variable
 * @line_num: line number (int)
 * @stack: pointer to stack
 * Return: type is char *
 */
char *get_opcode(char *text_line, unsigned int line_num, stack_t *stack)
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
			fprintf(stderr, "L%u: usage: push integer\n", line_num);
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
		{"add", add_func},
		{"nop", nop_func},
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
 * @line_num: unsigned integer
 *
 * Return: void
 */
void print_error(stack_t **stack, unsigned int line_num)
{
	fprintf(stderr, "L%u: unknown instruction %s\n", line_num, g_var.opcode);
	free(g_var.opcode);
	fclose(g_var.fp);
	free_stacklist(*stack);
	exit(EXIT_FAILURE);
}
