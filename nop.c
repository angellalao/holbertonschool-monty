#include "monty.h"

/**
 * nop_func - doesnt do anything
 * @stack: pointer to pointer to struct
 * @line_num: line number
 */
void nop_func(__attribute__((unused)) stack_t **stack, unsigned int line_num)
{
	if (line_num > 0)
	{
		;
	}
}
