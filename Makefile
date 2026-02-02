# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/20 15:12:35 by dufama            #+#    #+#              #
#    Updated: 2026/02/02 08:54:31 by dufama           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

G = \033[0;32m
B = \033[0;34m
Y = \033[0;33m
R = \033[0m

ARGS = 4 310 200 100

NAME = philo
CC = cc -g
CFLAGS = -Wall -Werror -Wextra -I.
SRC_DIR = src/
OBJ_DIR = obj/

MAIN = main.c

SRC_FILES = main.c \
			parsing.c \
			time.c \
			utils.c \
			free.c \
			action.c \
			init_mutex.c \
			init_philo.c \
			init_thread.c \
			init_monitor.c \


SRCS = $(addprefix $(OBJ_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(Y)--- Finalizing Compilation ---$(R)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(G)✅ $(NAME) created successfully!$(R)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(B)🔨 Compiling: $< $(R)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(G)[OK]$(R)"

clean:
	@echo "$(Y)Cleaning objects...$(R)"
	@rm -rf $(OBJ_DIR)
	@echo "$(G)Objects cleaned.$(R)"

fclean: clean
	@echo "$(Y)Removing $(NAME)...$(R)"
	@rm -f $(NAME)
	@echo "$(G)Cleanup complete.$(R)"

re: fclean all

#Debug
valgrind: all
	@echo "$(Y)--- Running Valgrind (leaks) ---$(R)"
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS)

helgrind: all
	@echo "$(Y)--- Running Helgrind (Data Races) ---$(R)"
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

#gdb

gdb: all
	@echo "$(Y)--- Lauching GDB ---$(R)"
	gdb --args ./$(NAME) $(ARGS)

.PHONY: all clean fclean re valgrind helgrind gdb
