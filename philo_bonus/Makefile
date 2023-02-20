################################################################################
##                                PHILOSOPHERS                                ##
################################################################################

NAME    := philo_bonus
INCLUDE := philo.h
OBJ_DIR := obj
SOURCES := main.c parse.c control.c actions.c monitor.c utils.c
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

.PHONY: leaks
leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes \
	./$(NAME) 4 310 200 100 1

.PHONY: hel
hel: all
	valgrind --tool=helgrind --trace-children=yes ./$(NAME) 4 310 200 100 1

.PHONY: drd
drd: all
	valgrind --tool=drd --trace-children=yes ./$(NAME) 4 310 200 100 1

.PHONY: clean
clean:
	$(RM) $(NAME)

.PHONY: fclean
fclean: clean
	$(RM) $(OBJECTS)
	$(RM) -r $(OBJ_DIR)

.PHONY: re
re: fclean all
