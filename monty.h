#ifndef __MONTY_H__
#define __MONTY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdarg.h>
#include <ctype.h>

#define MAX_BYTES 1024

/**
 * struct line_data - data extracted from line of monty file
 * @opcode: first token of line
 * @arg: second token of line
 *
 * Description: a struct to store the opcode and argument from a monty file
 */
typedef struct line_data
{
	char *opcode;
	int arg;
	FILE *fp;
} data_t;

data_t g_var;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void check_arguments(int argc);
FILE *x_fopen(char *filename);
char *my_getline(FILE *fp);
char *get_opcode(char *text_line, unsigned int line_number, stack_t *stack);
void (*get_op_func(char *str))(stack_t **, unsigned int);
size_t stacklist_len(stack_t *head);
int check_digit(char *str);
void set_g_var_memory();
void free_stacklist(stack_t *head);
void print_error(stack_t **stack, unsigned int line_number);
void push_func(stack_t **stack, unsigned int line_number);
void print_all(stack_t **stack, unsigned int line_number);
void pint_func(stack_t **stack, unsigned int line_number);
void pop_func(stack_t **stack, unsigned int line_number);
void swap_func(stack_t **stack, unsigned int line_number);

#endif /* __MONTY_H__ */
