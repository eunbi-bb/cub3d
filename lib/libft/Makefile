# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: gozturk <gozturk@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/11 18:39:50 by gozturk       #+#    #+#                  #
#    Updated: 2023/04/28 13:52:22 by gozturk       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c \
			ft_bzero.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_split.c \
			get_next_line.c \
			get_next_line_utils.c \
			./libftprintf/ft_putchar.c \
			./libftprintf/ft_putnbr.c \
			./libftprintf/ft_putstr.c \
			./libftprintf/ft_puthexlow.c \
			./libftprintf/ft_puthexupp.c \
			./libftprintf/ft_putaddr.c \
			./libftprintf/ft_putunsigned.c \
        		ft_printf.c

SRCB = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
		   	ft_lstmap_bonus.c

CC = cc

CFLAGS = -Wall -Werror -Wextra 

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

%.o : %.c
			$(CC) $(CFLAGS) -c $< -o $@

ifdef WITH_BONUS
SRC += $(SRCB)
endif

all : $(NAME)

bonus :
	$(MAKE) WITH_BONUS=1
#bonus : $(OBJ) $(OBJB)
#			ar rc $(NAME) $^

$(NAME) : $(OBJ) 
			ar rc $@ $? 

clean :
			rm -f $(OBJ) $(OBJB)
			rm -f ./libftprintf/*.o

fclean :	clean
			rm -f $(NAME)

re : fclean all

.PHONY = all clean fclean re bonus

