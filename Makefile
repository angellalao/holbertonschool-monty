CC = gcc
SRC = *.c
OBJ = $(SRC:.c=.o)
NAME = monty
RM = rm
CFLAGS = -Wall -Werror -Wextra -pedantic

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

test: $(SRC)
	$(CC) $(SRC) -o test

clean:
	$(RM) -f *~ $(NAME)

oclean:
	$(RM) -f $(OBJ)

fclean: clean oclean

re: oclean all

retest: fclean test
