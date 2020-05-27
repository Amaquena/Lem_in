# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 12:39:12 by amaquena          #+#    #+#              #
#    Updated: 2020/05/27 09:31:51 by krissyleemc      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in.a
LEM-IN = lem-in
CFILES = util.c rooms.c links.c solve.c
OFILES = $(CFILES:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror -ggdb3
LIBFT = -L./libft -lft

lft:
	@$(MAKE) -C libft all
lftclean:
	@$(MAKE) -C libft clean
lftfclean:
	@$(MAKE) -C libft fclean
lftre:
	@$(MAKE) -C libft re

$(NAME):
	@$(CC) -c $(FLAGS) $(CFILES)
	@ar rcs $(NAME) $(OFILES)

all: $(LEM-IN)
clean:
	@rm -f $(OFILES)

fclean: clean
	@echo "\ncleaning libft..."
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
	@echo "\ncompiling libft..."
	@cd libft && make all
	@echo "___________________________________"
	@echo "\nlibft compiled successfully"
	@echo "___________________________________\n"
	@echo "compiling Lem-in..."
	@$(CC) $(FLAGS) $(LEM-IN).c $(NAME) $(LIBFT) -o $(LEM-IN)
	@echo "___________________________________"
	@echo "\nLem-in compiled successfully"
	@echo "___________________________________"

debug: re
	$(CC) -g $(FLAGS) $(LEM-IN).c $(CFILES) $(LIBFT) -o $(LEM-IN)
	@echo "______________________________________________________________________\n"

# main: mainc
# 	$(CC) $(FLAGS) main.c $(LIBFT) -o main

# mainc:
# 	rm -fr main
