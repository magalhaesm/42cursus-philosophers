################################################################################
##                                PHILOSOPHERS                                ##
################################################################################

NAME    := philo
INCLUDE := philo.h
SOURCES := philo.c parse.c control.c
CFLAGS  := -Wall -Werror -Wextra -g

.PHONY: all
all: $(NAME)

$(NAME): $(SOURCES)
	$(CC) $^ $(CFLAGS) -o $@

.PHONY: clean
clean:
	$(RM) $(NAME)

.PHONY: fclean
fclean: clean

.PHONY: re
re: fclean all
