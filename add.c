#include "monty.h"

void add_func(stack_t **stack, unsigned int line_num)
{
	stack_t *head;
	stack_t *temp;
	size_t len;

	len = stacklist_len(*stack);
	if (len < 2)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}
	head = *stack;
	temp = head->next;
	temp->n = temp->n + head->n;
	temp->prev = NULL;
	*stack = temp;
	free(head);
}
