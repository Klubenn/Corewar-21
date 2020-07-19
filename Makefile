NAME = asm

LIBFT_DIR = ./libft/
LIBFT = lft
PRINTF_DIR = ./libft/ft_printf/
PRINTF = lftprintf
LIBFTPRINTF = ./libft/ft_printf/libftprintf.a
LIBFTLIB = ./libft/libft.a

INCL_DIR = ./includes/
INCL_H = asm.h op.h
INCL = $(addprefix $(INCL_DIR),$(INCL_H))

SRC_DIR = ./src/
SRC_C = asm.c to_bytecode.c checks.c labels.c op.c free_data.c champ_exec_code.c gnl.c split_corewar.c
SRC = $(addprefix $(SRC_DIR),$(SRC_C))

FLAGS = -Wall -Wextra -Werror

all: $(LIBFT_DIR)$(LIBFT) $(NAME)

$(LIBFT_DIR)$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(SRC) $(INCL) $(LIBFTLIB) $(LIBFTPRINTF)
	gcc $(FLAGS) $(SRC) -I$(INCL_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR)includes -L$(LIBFT_DIR) -$(LIBFT) -L$(PRINTF_DIR) -$(PRINTF) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(SRC_O)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re