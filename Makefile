# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 15:45:19 by sham              #+#    #+#              #
#    Updated: 2022/02/10 18:37:29 by sham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
CFLAGS = -Werror -Wall -Wextra
LIBRARY = ./mlx/minilibx_opengl_20191021
COMFILE_FLAGS = -I $(LIBRARY) -I ./header
LINKING_FLAGS = -lmlx -L $(LIBRARY) -framework OpenGL -framework AppKit
MAIN_SRCS = $(addprefix src/, main.c)
# MAIN_SRCS = ./test.c
PRINT_SRCS = $(addprefix src/print/, print.c)
RAY_SRCS = $(addprefix src/ray/, ray.c)
SCENE_SRCS = $(addprefix src/scene/, scene.c canvas.c)
UTILS_SRCS = $(addprefix src/utils/, vec3_util.c)

MAIN_OBJS = $(MAIN_SRCS:.c=.o)
PRINT_OBJS = $(PRINT_SRCS:.c=.o)
RAY_OBJS = $(RAY_SRCS:.c=.o)
SCENE_OBJS = $(SCENE_SRCS:.c=.o)
UTILS_OBJS = $(UTILS_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(MAIN_OBJS) $(PRINT_OBJS) $(RAY_OBJS) $(SCENE_OBJS) $(UTILS_OBJS)
		$(CC) $(CFLAGS) $(LINKING_FLAGS) $(MAIN_OBJS) $(PRINT_OBJS) $(RAY_OBJS) $(SCENE_OBJS) $(UTILS_OBJS) -o $(NAME)
%.o: %.c
		$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c $< -o $@

clean :
		rm -rf $(MAIN_OBJS) $(PRINT_OBJS) $(RAY_OBJS) $(SCENE_OBJS) $(UTILS_OBJS)

fclean : clean
		rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re