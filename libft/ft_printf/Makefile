# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 13:58:43 by gtristan          #+#    #+#              #
#    Updated: 2020/07/27 16:07:57 by gtristan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
INCL = ./
INCL_H = header_pf.h
INCLUDES = $(addprefix $(INCL),$(INCL_H))
INCL_LIB = ./../libft.h

SRC_DIR = src/
SRC_C = analysis.c decimal.c float2.c float4.c ft_printf.c parsing.c \
  		printnum.c services_itoa.c create_string.c float.c float3.c free.c \
		oct.c print_color.c putchar_str.c string_char.c make_result_str.c
SRC = $(addprefix $(SRC_DIR),$(SRC_C))

OBJ_DIR = obj/
OBJ_O = $(SRC_C:%.c=%.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_O))
LIB_A = ../libft.a

FLAGS =	-Wall -Werror -Wextra

all: $(OBJ_DIR) $(LIB_A) $(INCLUDES) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(SRC) $(OBJ)
	ar rc $(NAME) $(OBJ) $(LIB_A)
	ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCL)$(INCL_H)
	gcc $(FLAGS) -I $(INCL) -I../ -o $@ -c $<

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean flcean re
