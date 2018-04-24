# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbauguen <vbauguen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 11:26:20 by vbauguen          #+#    #+#              #
#    Updated: 2016/06/06 14:54:34 by vbauguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKEFLAGS += --silent

NAME = scop

SRC = 	src/main.c\
		src/log_functions.c\
		src/matrix_functions.c\
		src/matrix_continued.c\
		src/faces.c\
		src/bmp_parser.c\
		src/loaders.c\
		src/vertices.c\

OBJ = $(SRC:.c=.o)

GCCF = -Wall -Werror -Wextra -g

CFLAGS = 	-L libft -lft \
			-L /Users/vbauguen/.brew/Cellar/glew/2.1.0/lib -lGLEW  	-framework OpenGL \
			-L /Users/vbauguen/.brew/Cellar/glfw/3.2.1/lib -lglfw	-framework OpenGL

INCLUDE = 	-I libft/  \
			-I /Users/vbauguen/.brew/Cellar/glew/2.1.0/include \
			-I /Users/vbauguen/.brew/Cellar/glfw/3.2.1/include

all: $(NAME)

$(NAME): $(OBJ)	
	@make -C libft 
	@gcc -o $(NAME) $(OBJ)  $(CFLAGS)


%.o: %.c libft/libft.h
	gcc -c $(GCCF) $(INCLUDE) $< -o $@

.PHONY: clean fclean re

clean:
	@rm -rf $(OBJ)
	# @make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	# @make -C libft fclean

re: fclean all
