#include <stdbool.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include "corewar.h"
#include "libft/libft.h"
#include <fcntl.h>
#include "op.h"

void 	op16(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;
	u_int8_t	args_type_code;

	regnum = vm_field_memory->field[(player_process->PC + 2) % MEM_SIZE];
	if (regnum > 0 && regnum <= REG_NUMBER && game_process->aff)
		ft_putchar(player_process->registers[regnum * REG_SIZE - REG_SIZE]);
	move_pc_not_valid(game_process->op_tab, player_process);
}

void	op12(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	t_player_process *new;

	new = player_process;
	while (new->prev)
		new = new->prev;
	new->prev = (t_player_process *)malloc(sizeof(t_player_process));
	ft_memcpy(new->prev, player_process, sizeof(t_player_process));
	new->prev->PC = (short)vm_field_memory->field[player_process->PC + 1] % IDX_MOD;
	new->prev->next = new;
	new->prev->prev = NULL;
	player_process->PC += 3;
}

void	op15(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	t_player_process *new;

	new = player_process;
	while (new->prev)
		new = new->prev;
	new->prev = (t_player_process *)malloc(sizeof(t_player_process));
	ft_memcpy(new->prev, player_process, sizeof(t_player_process));
	new->prev->PC = (new->prev->PC + (short)vm_field_memory->field[player_process->PC + 1]) % MEM_SIZE;
	new->prev->next = new;
	new->prev->prev = NULL;
	player_process->PC += 3;
}

u_int32_t	put_value_to_arg(t_vm_field_memory *vm_field_memory, u_int64_t tmpPC, int size, u_int8_t type)
{
	u_int32_t number;
	u_int32_t tmp;
	int i;

	number = 0;
	i = 0;
	while(i < size)
	{
		tmp = (u_int8_t)(vm_field_memory->field[tmpPC % MEM_SIZE]);
		tmp = tmp >> (i * 8);
		number = number | tmp;
		tmpPC++;
		i++;
	}
	if (type == T_IND)
		return (put_value_to_arg(vm_field_memory, number, size, T_DIR));
	return (number);
}

void	op11(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;
	u_int32_t	arg_value[3];
	int i;
	u_int32_t tmp;
	u_int64_t tmpPC;

	tmpPC = (player_process->PC + 2) % MEM_SIZE;
	regnum = vm_field_memory->field[tmpPC];
	tmpPC += 1;
	i = 1;
	while (i < 3)
	{
		if (player_process->args[i] == T_REG)
		{
			tmp = (u_int8_t)vm_field_memory->field[(tmpPC) % MEM_SIZE];
			if (tmp < 1 || tmp > REG_NUMBER)
				move_pc_not_valid(game_process->op_tab, player_process);
			arg_value[i] = (u_int32_t)(player_process->registers[tmp - REG_SIZE]);
			tmpPC += 1;
		}
		else
		{
			arg_value[i] = put_value_to_arg(vm_field_memory, tmpPC, 2, player_process->args[i]);
			tmpPC += 2;
		}
		i++;
	}
	if (regnum > 0 && regnum <= REG_NUMBER)
		vm_field_memory->field[arg_value[1] + arg_value[2] % IDX_MOD] =
				(int)(player_process->registers[regnum - REG_SIZE]);
	move_pc_not_valid(game_process->op_tab, player_process);
}

void (*operation[16])(t_game_process *game_process, t_player_process *player_process,
					  t_player_list *player_list, t_vm_field_memory *vm_field_memory) =
		{
				op01(game_process, player_process, player_list, vm_field_memory),
				op02(game_process, player_process, player_list, vm_field_memory),
				op03(game_process, player_process, player_list, vm_field_memory),
				op04(game_process, player_process, player_list, vm_field_memory),
				op05(game_process, player_process, player_list, vm_field_memory),
				op06(game_process, player_process, player_list, vm_field_memory),
				op07(game_process, player_process, player_list, vm_field_memory),
				op08(game_process, player_process, player_list, vm_field_memory),
				op09(game_process, player_process, player_list, vm_field_memory),
				op10(game_process, player_process, player_list, vm_field_memory),
				op11(game_process, player_process, player_list, vm_field_memory),
				op12(game_process, player_process, player_list, vm_field_memory),
				op13(game_process, player_process, player_list, vm_field_memory),
				op14(game_process, player_process, player_list, vm_field_memory),
				op15(game_process, player_process, player_list, vm_field_memory),
				op16(game_process, player_process, player_list, vm_field_memory),

		};

