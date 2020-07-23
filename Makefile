NAME_ASM = asm
NAME_VM = corewar

LIBFT_DIR = ./libft/
LIBFT = lft
PRINTF_DIR = ./libft/ft_printf/
PRINTF = lftprintf
LIBFTPRINTF = ./libft/ft_printf/libftprintf.a
LIBFTLIB = ./libft/libft.a

INCL_DIR_ASM = ./includes_asm/
INCL_H_ASM = asm.h \
         op.h \
         structs.h
INCL_ASM = $(addprefix $(INCL_DIR_ASM),$(INCL_H_ASM))

#INCL_DIR_VM = ./includes_vm/
#INCL_H_VM = ###################################################
#INCL_VM = $(addprefix $(INCL_DIR_VM),$(INCL_H_VM))

SRC_DIR_ASM = ./src_asm/
SRC_C_ASM = asm.c \
        bin_arguments.c \
        champ_exec_code.c \
        check_params.c \
        checks.c \
        create_instruction.c \
        free_data.c \
        gnl.c \
        instruction_size.c \
        labels_atoi.c \
        labels_instructions.c \
        op.c \
        read_name_comment.c \
        skips.c \
        split_corewar.c \
        to_bytecode.c
SRC_ASM = $(addprefix $(SRC_DIR_ASM),$(SRC_C_ASM))

#SRC_DIR_VM = ./src_vm/
#SRC_C_VM = ###################################################################
#SRC_VM = $(addprefix $(SRC_DIR_VM),$(SRC_C_VM))

FLAGS = -Wall -Wextra -Werror

all: $(LIBFT_DIR)$(LIBFT) $(NAME_ASM) #$(NAME_VM)

$(LIBFT_DIR)$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME_ASM): $(SRC_ASM) $(INCL_ASM) $(LIBFTLIB) $(LIBFTPRINTF)
	gcc $(FLAGS) $(SRC_ASM) -I$(INCL_DIR_ASM) -I$(LIBFT_DIR) -I$(PRINTF_DIR)includes -L$(LIBFT_DIR) -$(LIBFT) -L$(PRINTF_DIR) -$(PRINTF) -o $(NAME_ASM)

#$(NAME_VM): $(SRC_VM) $(INCL_VM) $(LIBFTLIB) $(LIBFTPRINTF)
#	gcc $(FLAGS) $(SRC_VM) -I$(INCL_DIR_VM) -I$(LIBFT_DIR) -I$(PRINTF_DIR)includes -L$(LIBFT_DIR) -$(LIBFT) -L$(PRINTF_DIR) -$(PRINTF) -o $(NAME_VM)

clean:
	make clean -C $(LIBFT_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME_ASM) $(NAME_VM)

re: fclean all

.PHONY: all clean fclean re
