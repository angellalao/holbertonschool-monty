#include "monty.h"

void check_arguments(int argc);
FILE *x_fopen(char *filename);
char *my_getline(FILE *fp);
char *get_opcode(char *text_line);

int global_argument;

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
	global_argument = 0;

	check_arguments(argc);
	fp = x_fopen(argv[1]);
	bytes_read = getline(&buffer, &n, fp);
	while (bytes_read >= 0)
	{
		opcode = get_opcode(buffer);
		//get_op_func(opcode)(XXstack, line_number);
		free(opcode);
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
 * my_getline - short description
 * @argument: a unsigned int *data type variable
 * @line_number: a unsigned int *data type variable
 *
 * Return: type is char *
 */

/*char *my_getline(FILE *fp)
{
	char *line = NULL;
	char *buffer = NULL;
	ssize_t getline_return = 0;
	size_t n = 0;

	getline_return = getline(&buffer, &n, fp);
	if (getline_return == -1)
	{
		free(buffer);
		return (NULL);
	}
	line = strdup(buffer);
	free(buffer);
	return (line);
}*/

/**
 * get_opcode - short description
 * @text_line: a char *data type variable
 *
 * Return: type is char *
 */

char *get_opcode(char *text_line)
{
	char *return_value;
	char *token;
	char *delimeter = " \t\n";

	global_argument = 0;
	token = strtok(text_line, delimeter);
	if (token == NULL)
	{
		return (NULL);
	}
	return_value = strdup(token);
	if (strcmp(token, "push") == 0)
	{
		token = strtok(NULL, delimeter);
		global_argument = atoi(token);
	}
	printf("return value: %s / global_arg: %d\n", return_value, global_argument);
	return (return_value);
}
