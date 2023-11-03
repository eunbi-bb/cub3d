NAME		= cub3d
CC			= cc
ifdef DEBUG
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
else
CFLAGS		= -Wall -Wextra -Werror -g
endif

LIBMLX		= ./lib/MLX42
LIBFT		= ./lib/libft/libft.a
LIBS		= $(LIBMLX)/build/libmlx42.a -Iinclude -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit

OBJ_DIR		= obj/
SRC_DIR		= src/

HEADER_DIR	= include/
HEADER_SRC	= cub3d.h
HEADERS		= $(addprefix $(HEADER_DIR), $(HEADER_SRC))

INCLUDES	= -I $(HEADER_DIR) ./lib/libft/ -I $(LIBMLX)/include/

SRC_DIR		= src/
SRC_FILE	= main.c

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

OBJF		=	.cache_exists

CYAN_B		=	\033[1;96m
CYAN		=	\033[0;96m

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJ) $(OBJF)
		@make -C $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME) 
		@echo "- Minishell is compiled -"

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADER)| $(OBJF)
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(LIBFT) $(LIBS) $(INCLUDES) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)
		@touch $(OBJF)

clean:
		@rm -rf $(OBJ_DIR)
		@rm -rf $(LIBMLX)/build
		@make clean -C $(LIBFT)
		@rm -f $(OBJF)
		@echo "$(CYAN)- Object files are cleaned -"

fclean: clean
		@rm -f $(NAME)
		@make fclean -C $(LIBFT)
		@echo "$(CYAN)- Executable files are cleaned -"

re:	fclean all

.PHONY: all clean fclean re