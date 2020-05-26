# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: krissyleemc <krissyleemc@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 12:39:12 by amaquena          #+#    #+#              #
#    Updated: 2020/05/26 20:46:33 by krissyleemc      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in.a
LEM-IN = lem-in
CFILES = util.c rooms.c links.c solve.c
OFILES = $(CFILES:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror
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
	@rm -f $(LEM-IN)
	@rm -f $(NAME)
re: fclean all
	@echo "\n\t\t---COMPLETED---\n"

$(LEM-IN): $(NAME)
	$(CC) $(FLAGS) $(LEM-IN).c $(NAME) $(LIBFT) -o $(LEM-IN)



debug: re
	$(CC) -g $(FLAGS) $(LEM-IN).c $(CFILES) $(LIBFT) -o $(LEM-IN)
	@echo "______________________________________________________________________\n"

main: mainc
	$(CC) $(FLAGS) main.c $(LIBFT) -o main

mainc:
	rm -fr main

	
# $(CHCK):  $(NAME)
# 	$(CC) $(FLAGS) $(CHCK).c $(NAME) $(LIBFT) -o $(CHCK)
# 	@echo "______________________________________________________________________\n"
# $(PUSH):  $(NAME)
# 	$(CC) $(FLAGS) $(PUSH).c $(NAME) $(LIBFT) -o $(PUSH)
# 	@echo "______________________________________________________________________\n"


# Used to compile for usding gdb debugger
# cgcc: re
# pgcc: re
# 	$(CC) -g $(FLAGS) push_swap.c $(CFILES) $(LIBFT) -o push_swap
# 	@echo "______________________________________________________________________\n"
