NAME		= cub3d
CC			= cc
ifdef DEBUG
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
else
CFLAGS		= -Wall -Wextra -Werror -g
endif

LIBMLX		= ./lib/MLX42
LIBFT		= ./lib/libft

GLFW		= /opt/homebrew/Cellar/glfw/3.3.9/

ifdef LINUX
LIBS		= $(LIBMLX)/build/libmlx42.a -Iinclude -ldl -lglfw -pthread
else
LIBS	= $(LIBMLX)/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.9/lib/"
endif

MATH		= -lm

OBJ_DIR		= obj/

HEADER_DIR	= include/
HEADER_SRC	= cub3d.h
HEADERS		= $(addprefix $(HEADER_DIR), $(HEADER_SRC))

ifdef LINUX
INCLUDES	= -I $(HEADER_DIR) -I $(LIBMLX)/include/
else
INCLUDES	= -I $(HEADER_DIR) -I $(LIBMLX)/include/ -I $(GLFW)/include/
endif

SRC_DIR		= src/
SRC_FILE	= main.c \
				parser.c \
				error.c \
				free.c \
				handle_file.c \
				utils.c \
				file_extension.c \
				file_content_validation.c \
				map.c \
				seperate_file_content.c \
				setting_texture_paths.c \
				setting_colors.c \
				map_validation.c \
				check_walls.c \
				test.c \
				render.c \
				init.c \
				textures.c \
				luminosity.c
#	draw_map.c

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

OBJF		=	.cache_exists

CYAN_B		=	\033[1;96m
CYAN		=	\033[0;96m

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j4

$(NAME): $(OBJ) $(OBJF)
		@make -C $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(LIBFT)/libft.a -o $(NAME) $(MATH)
		@echo "- cub3d is compiled -"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)| $(OBJF)
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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