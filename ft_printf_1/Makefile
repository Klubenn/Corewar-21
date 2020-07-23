# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/17 13:58:43 by gtristan          #+#    #+#              #
#    Updated: 2020/07/23 23:54:41 by gtapioca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

INCL = ./includes/
INCL_H = header_pf.h
INCLUDES = $(addprefix $(INCL),$(INCL_H))
INCL_LIB = ../

SRC_DIR = src/
SRC_C = analysis.c decimal.c float2.c float4.c ft_printf.c parsing.c \
  		printnum.c services_itoa.c create_string.c float.c float3.c free.c \
		oct.c print_color.c putchar_str.c string_char.c make_result_str.c
SRC = $(addprefix $(SRC_DIR),$(SRC_C))

OBJ_DIR = obj/
OBJ_O = $(SRC_C:%.c=%.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_O))
LIB_O = ../ft_strlen.o ../ft_atoi.o ../ft_strjoin.o ../ft_strncpy.o ../ft_strcpy.o

FLAGS =	-Wall -Werror -Wextra

all: $(OBJ_DIR) $(NAME) $(LIB_O) $(INCLUDES)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(SRC) $(OBJ) 
	ar rc $(NAME) $(OBJ) $(LIB_O)
	ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCL)$(INCL_H)
	gcc $(FLAGS) -I $(INCL) -o $@ -c $<

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean flcean re
