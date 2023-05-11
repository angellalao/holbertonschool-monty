#include "monty.h"

/**
 * push_func - short description
 * @stack: a stack_t **data type variable
 * @line_num: a unsigned int data type variable
 *
 * Return: type is void
 */
void push_func(stack_t **stack, __attribute__((unused)) unsigned int line_num)
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
 * @line_num: a unsigned int data type variable
 *
 * Return: type is void
 */
void print_all(stack_t **stack, __attribute__((unused)) unsigned int line_num)
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
