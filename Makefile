# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 12:59:39 by pgrossma          #+#    #+#              #
#    Updated: 2023/12/06 14:47:08 by pgrossma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	src/pipex.c src/parse.c
OBJ = $(SRC:%.c=%.o)

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
INC = -I libft -I src
LIB = libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(LIB) $^ -o $(NAME) $(INC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME).a

re: fclean all
