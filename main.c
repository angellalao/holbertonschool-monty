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
