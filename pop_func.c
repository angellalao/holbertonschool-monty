#include "monty.h"

/**
 * pop_func - short description
 * @stack: a stack_t **data type variable
 * @line_number: a unsigned int data type variable
 *
 * Return: type is void
 */
void pop_func(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	*stack = temp->next;
	if (temp->next != NULL)
	{
		temp->next->prev = NULL;
	}
	free(temp);
}
