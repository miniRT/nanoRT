# =============================================================================
# Color Variables
# =============================================================================

BLACK		= 	"\033[0;30m"
GRAY		= 	"\033[1;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
PURPLE		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[1;37m"
EOC			=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

# =============================================================================
# Command Variables
# =============================================================================

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
MLXFLAG		=	-L ./mlx -I ./mlx -lmlx -framework Appkit -framework opengl
MLX			=	./mlx/libmlx.a
RM			=	rm -f

# =============================================================================
# File Variables
# =============================================================================

NAME		=	miniRT
HEADER		=	./includes/
MINIRT_DIR	=	./srcs/
D_UTILS		=	./utils/
D_SCENE		=	./scene/
D_TRACE		=	./trace/
D_PARSE		=	./parse/
D_VALID		=	./validator/
D_MLX		=	./mlx/
SRC_LIST	=	main.c							\
				${D_UTILS}init_units.c			\
				${D_UTILS}vec_utils1.c			\
				${D_UTILS}vec_utils2.c			\
				${D_UTILS}vec_utils3.c			\
				${D_UTILS}object_utils.c		\
				${D_UTILS}print.c				\
				${D_UTILS}hit_utils.c			\
				${D_SCENE}scene.c				\
				${D_SCENE}object_create.c		\
				${D_TRACE}ray/ray.c				\
				${D_TRACE}ray/phong_lighting.c	\
				${D_TRACE}hit/hit.c				\
				${D_TRACE}hit/hit_sphere.c		\
				${D_TRACE}hit/hit_plane.c		\
				${D_TRACE}hit/hit_cylinder.c	\
				${D_TRACE}hit/normal.c			\
				${D_PARSE}file_open.c			\
				${D_PARSE}ft_get_next_line.c	\
				${D_PARSE}ft_replace.c			\
				${D_PARSE}ft_strdup.c			\
				${D_PARSE}ft_strjoin.c			\
				${D_PARSE}ft_strlcpy.c			\
				${D_PARSE}ft_strlen.c			\
				${D_PARSE}ft_cmpstr.c			\
				${D_PARSE}ft_atoi.c				\
				${D_PARSE}ft_split.c			\
				${D_PARSE}ft_isdigit.c			\
				${D_PARSE}ft_isspace.c			\
				${D_PARSE}ft_putstr_fd.c		\
				${D_PARSE}ft_atof.c				\
				${D_PARSE}ft_strcmp.c			\
				${D_PARSE}free_all.c			\
				${D_PARSE}error_disposal.c		\
				${D_VALID}valid1.c				\
				${D_VALID}valid2.c				\
				${D_VALID}valid3.c				\
				${D_MLX}mlx_utils.c				\

SRCS		=	$(addprefix $(MINIRT_DIR), $(SRC_LIST))
OBJS		=	$(SRCS:.c=.o)

# =============================================================================
# Target Generating
# =============================================================================

%.o			:	%.c
				@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

$(NAME)		:	$(OBJS)
				@echo $(GREEN) "Source files are compiled!\n" $(EOC)
				@echo $(WHITE) "Building $(NAME) for" $(YELLOW) "Mandatory" $(WHITE) "..." $(EOC)
				@$(CC) $(CFALGS) $(MLXFLAG) -I $(HEADER) -o $(NAME) $(OBJS)
				@echo $(GREEN) "$(NAME) is created!\n" $(EOC)

# =============================================================================
# Rules
# =============================================================================

.PHONY		:	all
all			:	$(NAME)

.PHONY		:	clean
clean		:
				@echo $(YELLOW) "Cleaning object files..." $(EOC)
				@$(RM) $(OBJS)
				@echo $(RED) "Object files are cleaned!\n" $(EOC)

.PHONY		:	fclean
fclean		:	clean
				@echo $(YELLOW) "Removing $(NAME)..." $(EOC)
				@$(RM) $(NAME)
				@echo $(RED) "$(NAME) is removed!\n" $(EOC)

.PHONY		:	re
re			:	fclean all

.PHONY		:	norm
norm		:
				@norminette

