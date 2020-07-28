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

INCL_DIR_VM = ./includes_vm/
INCL_H_VM = corewar.h op.h
INCL_VM = $(addprefix $(INCL_DIR_VM),$(INCL_H_VM))

SRC_DIR_ASM = src_asm/
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

SRCS_C_VM = src_vm/

SRC_C_VM = memory_deleter.c move_programming_counter.c player_list_deleter.c \
			print_logs.c processes_deleter.c validation_for_args_type.c \
			virtual_machine_game_mechanic.c virtual_machine_operations_executing.c \
			vm_field_memory_allocator.c winner_definer.c \
			alives_checker.c check_players.c \
			check_players_position.c \
			memory_allocator_for_cmd_line_arguments.c \
			parse_v_n_d_dump.c \
			player_stack_creator_2.c \
			players_stack_creator.c \
			print_usage_and_check_atoi_honest.c \
			processes_creator.c \
			put_in_stack_of_players.c \
			reader_and_setter_players_parameters.c \
			op1.c op11_op12_op15.c op14.c op2_op5.c op6_op7_op8_op9.c parse_arguments.c \
			take_value_from_field.c op10.c op13.c op16.c op4_op5_helper.c operation_completer.c \
			process_args_and_put_value.c main.c\


SRCS_VM = $(addprefix $(SRCS_C_VM),$(SRC_C_VM))

OBJ_DIR_VM = obj_vm/
OBJ_DIR_ASM = obj_asm/

OBJ_O_VM = $(SRC_C_VM:%.c=%.o)
OBJ_O_ASM = $(SRC_C_ASM:%.c=%.o)

OBJ_ASM = $(addprefix $(OBJ_DIR_ASM), $(OBJ_O_ASM))
OBJ_VM = $(addprefix $(OBJ_DIR_VM), $(OBJ_O_VM))

FLAGS = -Wall -Wextra -Werror

all: $(LIBFT_DIR)$(LIBFT) $(OBJ_DIR_VM) $(OBJ_DIR_ASM) $(NAME_VM) $(NAME_ASM)

$(OBJ_DIR_VM):
	mkdir -p $(OBJ_DIR_VM)

$(OBJ_DIR_ASM):
	mkdir -p $(OBJ_DIR_ASM)

$(LIBFT_DIR)$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME_ASM): $(INCL_ASM) $(SRC_ASM) $(OBJ_ASM)
	gcc $(FLAGS) $(OBJ_ASM) -I$(INCL_DIR_ASM) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -L$(PRINTF_DIR) -$(PRINTF) -L$(LIBFT_DIR) -$(LIBFT) -o $(NAME_ASM)

$(OBJ_DIR_ASM)%.o: $(SRC_DIR_ASM)%.c $(INCL_ASM)
	gcc $(FLAGS) -I $(INCL_DIR_ASM) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -o $@ -c $<

$(NAME_VM): $(INCL_VM) $(SRCS_VM) $(OBJ_VM)
	gcc $(FLAGS) $(OBJ_VM) -I$(INCL_DIR_VM) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -L$(PRINTF_DIR) -$(PRINTF) -L$(LIBFT_DIR) -$(LIBFT) -o $(NAME_VM)

$(OBJ_DIR_VM)%.o: $(SRCS_C_VM)%.c $(INCL_VM)
	gcc $(FLAGS) -I $(INCL_DIR_VM) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -o $@ -c $<

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR_VM)
	rm -rf $(OBJ_DIR_ASM)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR_VM)
	rm -rf $(OBJ_DIR_ASM)
	rm -f $(NAME_ASM) $(NAME_VM)

re: fclean all

.PHONY: all clean fclean re
