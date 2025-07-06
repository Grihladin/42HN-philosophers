NAME	:= philo

#################################
#			Config				#
#################################

CC	:= gcc

#################################
#			Flags				#
#################################

DEBUG_FLAGS	:= -g -fsanitize=address -fsanitize=undefined -O0
CFLAGS		:= -Wall -Wextra -Werror -g -pthread -Iinc

#################################
#			Directories			#
#################################

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

#################################
#			Files				#
#################################

SRC = \
main.c \
utils.c \
lst_fts.c \
printing.c \
protocol.c \
time.c \
initialisation.c \
death_check.c \
cleanup.c
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
SRC_PATHS = $(addprefix $(SRC_DIR)/, $(SRC))

#################################
#			Rules				#
#################################

all: $(NAME)
	@echo "\033[0;32m🎉 $(NAME) built successfully!\033[0m"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
