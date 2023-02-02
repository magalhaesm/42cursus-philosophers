################################################################################
##                                PHILOSOPHERS                                ##
################################################################################

NAME    := philo
INCLUDE := philo.h
OBJ_DIR := obj
SOURCES := philo.c parse.c control.c forks.c locks.c actions.c log.c monitor.c
OBJECTS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))
CFLAGS  := -Wall -Werror -Wextra -g
LDFLAGS := -lpthread

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c $(INCLUDE) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

.PHONY: check
check: all
	valgrind --tool=helgrind ./$(NAME) 4 310 200 100

.PHONY: clean
clean:
	$(RM) $(NAME)

.PHONY: fclean
fclean: clean
	$(RM) $(OBJECTS)
	$(RM) -r $(OBJ_DIR)

.PHONY: re
re: fclean all
