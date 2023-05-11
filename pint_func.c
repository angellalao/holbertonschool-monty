#include "monty.h"

/**
 * pint_func - short description
 * @stack: a stack_t **data type variable
 * @line_num: a unsigned int data type variable
 *
 * Return: type is void
 */
void pint_func(stack_t **stack, unsigned int line_num)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_num);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
