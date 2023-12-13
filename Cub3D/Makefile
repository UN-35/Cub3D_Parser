# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 11:49:19 by yoelansa          #+#    #+#              #
#    Updated: 2023/12/12 19:37:48 by yoelansa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC= parsing/main.c libft/*.c get_next_line/*.c

RM = @rm -rf

CC = @cc

CFLAGS = -Wextra -Werror -Wall  -fsanitize=address -g

all : $(NAME)

$(NAME) : $(SRC)
		${CC} $(CFLAGS) $(SRC) -o $(NAME)
		@echo "\x1b[32m \x1b[1m ✅ Mandatory Compelet..\n     Run \x1b[0m\x1b[33m./$(NAME)"

clean :
		@echo "\x1b[31m \x1b[1m ✅ Cleaning \x1b[32mSuccess\x1b[0m"

fclean : clean
		${RM} $(NAME)
		@echo "\x1b[31m \x1b[1m ✅ Delete [$(NAME)] \x1b[32mSuccess\x1b[0m"

re : fclean all