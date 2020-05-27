# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 12:39:12 by amaquena          #+#    #+#              #
#    Updated: 2020/05/27 20:47:43 by krissyleemc      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in.a
LEM-IN = lem-in
CFILES = util.c rooms.c links.c solve.c free.c solve_assist.c solve_assist2.c
OFILES = $(CFILES:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror -ggdb3 -g
LIBFT = -L./libft -lft

$(NAME):
	@$(CC) -c $(FLAGS) $(CFILES)
	@ar rcs $(NAME) $(OFILES)

all: $(LEM-IN)
clean:
	@rm -f $(OFILES)

fclean: clean
	@echo "\ncleaning libft...\n"
	@cd libft && make fclean
	@echo "___________________________________"
	@echo "\nlibft cleaned successfully"
	@echo "___________________________________"
	@echo "\ncleaning lem-in..."
	@rm -f $(LEM-IN)
	@rm -f $(NAME)
	@echo "___________________________________"
	@echo "\nLem-in cleaned successfully"
	@echo "___________________________________"
re: fclean all
	@echo "\n\t\t---COMPLETED---\n"

$(LEM-IN): $(NAME)
	@echo "\ncompiling libft...\n"
	@cd libft && make all
	@echo "___________________________________"
	@echo "\nlibft compiled successfully"
	@echo "___________________________________\n"
	@echo "compiling Lem-in..."
	@$(CC) $(FLAGS) $(LEM-IN).c $(NAME) $(LIBFT) -o $(LEM-IN)
	@echo "___________________________________"
	@echo "\nLem-in compiled successfully"
	@echo "___________________________________\n"

debug: re
	$(CC) -g $(FLAGS) $(LEM-IN).c $(CFILES) $(LIBFT) -o $(LEM-IN)
	@echo "______________________________________________________________________\n"

