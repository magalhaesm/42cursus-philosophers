################################################################################
##                                PHILOSOPHERS                                ##
################################################################################

NAME    := philo
INCLUDE := philo.h
SOURCES := philo.c parse.c control.c forks.c locks.c actions.c log.c monitor.c
CFLAGS  := -Wall -Werror -Wextra -g

.PHONY: all
all: $(NAME)

$(NAME): $(SOURCES) $(INCLUDE)
	$(CC) $^ $(CFLAGS) -o $@

.PHONY: check
check: all
	valgrind --tool=helgrind ./$(NAME) 4 310 200 100

.PHONY: clean
clean:
	$(RM) $(NAME)

.PHONY: fclean
fclean: clean

.PHONY: re
re: fclean all
