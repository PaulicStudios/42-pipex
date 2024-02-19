# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 12:59:39 by pgrossma          #+#    #+#              #
#    Updated: 2024/02/19 17:48:04 by pgrossma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	src/pipex.c src/parse.c src/execute_process.c
OBJ = $(SRC:%.c=%.o)

NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
INC = -I libft -I src
LIBDIR = ./libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(LIB) $^ -o $(NAME) -L $(LIBDIR) -lft $(INC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(NAME).a

re: fclean all
