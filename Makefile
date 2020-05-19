# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaquena <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 12:39:12 by amaquena          #+#    #+#              #
#    Updated: 2019/09/12 09:48:11 by amaquena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in.a
LEM_IN = lem_in
CFILES = display_functions.c rooms.c links.c solve.c
OFILES = $(CFILES:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = -L./libft -lft

lft:
	$(MAKE) -C libft all
lftclean:
	$(MAKE) -C libft clean
lftfclean:
	$(MAKE) -C libft fclean
lftre:
	$(MAKE) -C libft re

$(NAME):
	@$(CC) -c $(FLAGS) $(CFILES)
	@ar rcs $(NAME) $(OFILES)

all: $(LEM_IN)
clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(LEM_IN)
	@rm -f $(NAME)
re: fclean all
	@echo "\t\t---COMPLETED---\n"

$(LEM_IN): $(NAME)
	$(CC) $(FLAGS) $(LEM_IN).c $(NAME) $(LIBFT) -o $(LEM_IN)



debug:	re
	$(CC) -g $(FLAGS) $(LEM_IN).c $(CFILES) $(LIBFT) -o $(LEM_IN)
	@echo "______________________________________________________________________\n"
	
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