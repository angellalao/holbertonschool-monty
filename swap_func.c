#include "monty.h"

/**
 * swap_func - short description
 * @stack: a stack_t **data type variable
 * @line_number: a unsigned int data type variable
 *
 * Return: type is void
 */
void swap_func(stack_t **stack, unsigned int line_number)
{
	int temp;
	stack_t *head;
	size_t len;

	len = stacklist_len(*stack);
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	head = *stack;
	temp = head->n;
	head->n = head->next->n;
	head->next->n = temp;
	return;
}

/**
 * stacklist_len - returns the length of a doubly linked list
 * @head: head of stack_t linked list
 *
 * Return: number of nodes
 */
size_t stacklist_len(stack_t *head)
{
	size_t size = 0;
	stack_t *temp = head;

	while (temp != NULL)
	{
		temp = temp->next;
		size = size + 1;
	}
	return (size);
}
