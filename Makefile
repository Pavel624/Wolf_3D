NAME = wolf3d

SRC_FILES  = main.c additional.c keys.c movement.c
SRC_FOLDER = ./sources
INC_FOLDER = ./includes/
SRC = $(addprefix $(SRC_FOLDER)/, $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FOLDER = ./objs
OBJ = $(addprefix $(OBJ_FOLDER)/, $(OBJ_FILES))

FLAGS = -Wall -Werror -Wextra -O3

OSVER := $(shell uname -s)

ifeq ($(OSVER), Linux)
	LIBFLAGS = -lXext -lX11 minilibx/libmlx.a -g3 -lbsd -lm -lmlx
else
	LIBFLAGS = -framework OpenGL -framework AppKit -lm -lmlx
endif

LIBFT = libft/libft.a

INC_LIB = libft

HEAD = libft/libft.h

RED= \033[1;31m
GREEN= \033[1;32m
YELLOW= \033[1;33m
BLUE= \033[1;34m
VIOLET= \033[1;35m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@gcc $(FLAGS) $(OBJ) $(LIBFT) $(LIBFLAGS) -I $(INC_LIB) -o $(NAME)
	@echo "$(GREEN)Project is successfully compiled"

$(LIBFT):
	@make -C libft/
	@echo "$(GREEN)Compiling library files$(VIOLET)"

$(OBJ_FOLDER)/%.o : $(SRC_FOLDER)/%.c
	@mkdir -p $(OBJ_FOLDER)
	@gcc $(FLAGS) -c $< -o $@ -I$(INC_LIB) -I$(INC_FOLDER)

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@rm -rf $(OBJ_FOLDER)
	@echo "$(RED)Suspending library files$(VIOLET)"

fclean: clean
	@make -C libft fclean
	@rm -f $(OBJ)
	@rm -rf $(OBJ_FOLDER)
	@rm -f $(NAME)
	@echo "$(RED)Suspending project files$(VIOLET)"

re: fclean all

.PHONY: all clean fclean re