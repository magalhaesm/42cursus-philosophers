################################################################################
##                                PHILOSOPHERS                                ##
################################################################################

NAME    := philo
INCLUDE := philo.h
SOURCES := philo.c parse.c control.c forks.c forks_lock.c philosophers.c
CFLAGS  := -Wall -Werror -Wextra -g

.PHONY: all
all: $(NAME)

$(NAME): $(SOURCES) $(INCLUDE)
	$(CC) $^ $(CFLAGS) -o $@

.PHONY: check
check: all
	valgrind --tool=helgrind ./$(NAME) 10 800 200 200

.PHONY: clean
clean:
	$(RM) $(NAME)

.PHONY: fclean
fclean: clean

.PHONY: re
re: fclean all
