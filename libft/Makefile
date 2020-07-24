# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 09:18:49 by gtristan          #+#    #+#              #
#    Updated: 2020/07/24 23:05:50 by gtapioca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = ./
INCL_H = libft.h
INCL = $(addprefix $(INCLUDES),$(INCL_H))

SOURCE = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c \
	ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c \
	ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
	ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
	ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
	ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
	ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
	ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strlencmp.c ft_strmap.c \
	ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c \
	ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
	ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_strndup.c\
	ft_isspace.c ft_countwords.c ft_math.c ft_sort.c ft_strsort.c \
	ft_strnrdup.c get_next_line.c ft_atoi_base.c ft_new_two.c

DEST = $(SOURCE:%.c=%.o)

PRINTF_DIR = ft_printf/
PRINTF = lftprintf

NAME = libft.a
NAME_PRINTF = libftprintf.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(PRINTF_DIR)$(PRINTF)

$(NAME): $(SOURCE) $(DEST)
	ar rc $(NAME) $(DEST)
	ranlib $(NAME)

%.o: %.c $(INCL)
	gcc $(FLAGS) -I $(INCLUDES)  -o $@ -c $<

$(PRINTF_DIR)$(PRINTF):
	make -C $(PRINTF_DIR)

clean:
	rm -f $(DEST)
	make clean -C $(PRINTF_DIR)

fclean:
	rm -f $(DEST)
	rm -f $(NAME)
	make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean flcean re
