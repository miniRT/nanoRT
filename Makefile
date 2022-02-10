# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 15:45:19 by sham              #+#    #+#              #
#    Updated: 2022/02/10 15:56:45 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
CFLAGS = -Werror -Wall -Wextra
LIBRARY = ./mlx/minilibx_opengl_20191021
COMFILE_FLAGS = -I $(LIBRARY)
LINKING_FLAGS = -lmlx -L $(LIBRARY) -framework OpenGL -framework AppKit
# MAIN_SRCS = $(addprefix src/, main.c)
MAIN_SRCS = ./test.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(MAIN_OBJS) 
		$(CC) $(CFLAGS) $(LINKING_FLAGS) $(MAIN_OBJS) -o $(NAME)
%.o: %.c
		$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c $< -o $@

clean :
		rm -rf $(MAIN_OBJS) 

fclean : clean
		rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re