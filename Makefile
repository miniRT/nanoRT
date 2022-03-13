# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sham <sham@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/10 15:45:19 by sham              #+#    #+#              #
#    Updated: 2022/03/13 13:37:58 by sham             ###   ########.fr        #
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
# TRACE_SRCS = $(addprefix src/trace/, hit/hit_sphere.c ray/ray.c)
TRACE_SRCS = $(addprefix src/trace/, hit/hit.c hit/normal.c hit/hit_sphere.c hit/hit_plane.c hit/hit_cylinder.c ray/ray.c ray/phong_lighting.c)
SCENE_SRCS = $(addprefix src/scene/, scene.c object_create.c)
UTILS_SRCS = $(addprefix src/utils/, vec3_util.c object_utils.c)


MAIN_OBJS = $(MAIN_SRCS:.c=.o)
PRINT_OBJS = $(PRINT_SRCS:.c=.o)
TRACE_OBJS = $(TRACE_SRCS:.c=.o)
SCENE_OBJS = $(SCENE_SRCS:.c=.o)
UTILS_OBJS = $(UTILS_SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(MAIN_OBJS) $(PRINT_OBJS) $(TRACE_OBJS) $(SCENE_OBJS) $(UTILS_OBJS)
		$(CC) $(CFLAGS) $(LINKING_FLAGS) $(MAIN_OBJS) $(PRINT_OBJS) $(TRACE_OBJS) $(SCENE_OBJS) $(UTILS_OBJS) -o $(NAME)
%.o: %.c
		$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c $< -o $@

clean :
		rm -rf $(MAIN_OBJS) $(PRINT_OBJS) $(TRACE_OBJS) $(SCENE_OBJS) $(UTILS_OBJS)

fclean : clean
		rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re