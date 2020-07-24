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

SRCS_C_VM_VIRTUAL_MACHINE = src_vm/virtual_machine/
SRCS_C_VM_VALIDATION = src_vm/validation/
SRCS_C_VM_OPERATIONS = src_vm/operations/

SRC_C_VM_VIRTUAL_MACHINE = memory_deleter.c move_programming_counter.c player_list_deleter.c \
							print_logs.c processes_deleter.c validation_for_args_type.c \
							virtual_machine_game_mechanic.c virtual_machine_operations_executing.c \
							vm_field_memory_allocator.c winner_definer.c

SRC_C_VM_VALIDATION = alives_checker.c check_players.c \
                      check_players_position.c \
                      memory_allocator_for_cmd_line_arguments.c \
                      parse_v_n_d_dump.c \
                      player_stack_creator_2.c \
                      players_stack_creator.c \
                      print_usage_and_check_atoi_honest.c \
                      processes_creator.c \
                      put_in_stack_of_players.c \
                      reader_and_setter_players_parameters.c

SRC_C_VM_OPERATIONS = op1.c op11_op12_op15.c op14.c op2_op5.c op6_op7_op8_op9.c parse_arguments.c \
						take_value_from_field.c op10.c op13.c op16.c op4_op5_helper.c operation_completer.c \
						process_args_and_put_value.c

#SRC_C_VM = ###################################################################
SRCS_VM = $(addprefix $(SRCS_C_VM_VIRTUAL_MACHINE),$(SRC_C_VM_VIRTUAL_MACHINE)) $(addprefix $(SRCS_C_VM_OPERATIONS),$(SRC_C_VM_OPERATIONS)) $(addprefix $(SRCS_C_VM_VALIDATION),$(SRC_C_VM_VALIDATION))

OBJ_DIR_VM = obj_vm/
OBJ_DIR_ASM = obj_asm/

OBJ_O_VM = $(SRC_C_VM_VIRTUAL_MACHINE:%.c=%.o) $(SRC_C_VM_VALIDATION:%.c=%.o) $(SRC_C_VM_OPERATIONS:%.c=%.o)

OBJ_VM = $(addprefix $(OBJ_DIR_VM), $(OBJ_O_VM))

#SRC_DIR_VM = ./src_vm/

FLAGS = -Wall -Wextra -Werror

all: $(LIBFT_DIR)$(LIBFT) $(OBJ_DIR_VM) $(NAME_VM) #$(OBJ_DIR_ASM) $(NAME_ASM)

$(OBJ_DIR_VM):
	mkdir -p $(OBJ_DIR_VM)

$(OBJ_DIR_ASM):
	mkdir -p $(OBJ_DIR_ASM)

$(LIBFT_DIR)$(LIBFT):
	make -C $(LIBFT_DIR)
	@echo $(SRCS_VM)
#	@echo $(OBJ_VM)


#$(NAME_ASM): $(SRC_ASM) $(INCL_ASM) $(LIBFTLIB) $(LIBFTPRINTF)
#	gcc $(FLAGS) $(SRC_ASM) -I$(INCL_DIR_ASM) -I$(LIBFT_DIR) -I$(PRINTF_DIR)includes -L$(LIBFT_DIR) -$(LIBFT) -L$(PRINTF_DIR) -$(PRINTF) -o $(NAME_ASM)

$(NAME_VM): $(INCL_VM) $(SRCS_VM) $(OBJ_VM)
	gcc $(FLAGS) $(SRCS_VM) -I$(INCL_DIR_VM) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -L$(LIBFT_DIR) -$(LIBFT) -L$(PRINTF_DIR) -$(PRINTF) -o $(NAME_VM)

$(OBJ_DIR_VM)%.o: $(SRCS_C_VM_VIRTUAL_MACHINE)%.c $(INCL_VM)
	gcc $(FLAGS) -I $(INCL_DIR_VM) -o $@ -c $<

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR_VM)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME_ASM) $(NAME_VM)

re: fclean all

.PHONY: all clean fclean re
