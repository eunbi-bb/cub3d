NAME		= cub3D
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
				parser/parser.c \
				utils/error.c \
				utils/free.c \
				parser/handle_file.c \
				utils/utils.c \
				parser/file_extension.c \
				parser/file_content_validation.c \
				parser/map.c \
				parser/colors.c \
				parser/seperate_file_content.c \
				parser/setting_texture_paths.c \
				parser/setting_colors.c \
				parser/map_validation.c \
				parser/check_walls.c \
				utils/test.c \
				utils/init.c \
				render/draw.c \
				render/luminosity.c \
				render/move.c \
				render/ray_casting.c \
				render/render_utils.c \
				render/render.c \
				render/textures.c \

#	draw_map.c

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC_FILE:.c=.o))

OBJF		=	.cache_exists

CYAN_B		=	\033[1;96m
CYAN		=	\033[0;96m
GREEN_B		=	\033[1;32m
DEFAULT		=	\033[0m

all: libmlx $(NAME)

libmlx:
	@$(LIBMLX)/git submodule init
	@$(LIBMLX)/git submodule update
	@cmake $(LIBMLX) -B $(LIBMLX)/build && cmake --build $(LIBMLX)/build -j4

$(NAME): $(OBJ) $(OBJF)
		@make -C $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(LIBFT)/libft.a -o $(NAME) $(MATH)
		@echo "$(CYAN_B) - cub3d is compiled - $(DEFAULT)"

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
		@echo "$(CYAN)- Object files are cleaned - $(DEFAULT)"

fclean: clean
		@rm -f $(NAME)
		@make fclean -C $(LIBFT)
		@echo "$(CYAN)- Executable files are cleaned - $(DEFAULT)"

re:	fclean all

.PHONY: all clean fclean re