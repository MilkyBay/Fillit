# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pthuy <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 16:41:16 by pthuy             #+#    #+#              #
#    Updated: 2019/10/18 18:32:05 by pthuy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

FLAGS = -Wall -Wextra -Werror

SRC = main.c get_tetramino.c list.c crop_new.c map_constructor.c sorter.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): lib $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -L libft -lft

$(OBJ):
	gcc $(FLAGS) -c $(SRC) -I -Ilibft/includes/

lib:
	make -C libft

clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
