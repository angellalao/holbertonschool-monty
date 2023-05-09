#ifndef __MONTY_H__
#define __MONTY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <stdarg.h>

#define MAX_BYTES 1024;
extern int global_argument;

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

/* older fucntions: */
int is_executable(char *string);
void get_input(char **buffer, size_t *bufsize, ssize_t *getret);
void assign_words_to_array(char *str, char *argv[]);
int fork_child_adult(char **argv, char **environ, char **str);
void split_string_into_words(char *string, char **words);
char *get_env_string(char *env_key);
char *get_executable_string(char *path, char *program_name);
char *get_path(char **name, char *program_name);
int builtin_commands(char **argv, char **environ, int *status, char *str);
int print_env(char *envp[]);
DIR *_opendir(char *name);
struct dirent *_readdir(DIR *dp);

#endif /* __MONTY_H__ */
