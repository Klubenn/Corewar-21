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
	move_pc(game_process->op_tab, player_process);
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
	new->prev->PC = *((short *)&(vm_field_memory->field[player_process->PC + 1])) % IDX_MOD;
	new->prev->operation_code = vm_field_memory->field[new->prev->PC];
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
	new->prev->PC = (new->prev->PC + *((short *)(&(vm_field_memory->field[player_process->PC + 1])))) % MEM_SIZE;
	new->prev->operation_code = vm_field_memory->field[new->prev->PC];
	new->prev->next = new;
	new->prev->prev = NULL;
	player_process->PC += 3;
}

u_int32_t	put_value_to_arg(t_vm_field_memory *vm_field_memory,
				u_int64_t tmpPC, int size, u_int8_t type)//todo take_value_from_field
{
	u_int32_t number;
	u_int32_t tmp;
	int i;

	number = 0;
	i = 0;
	while(i < size)
	{
		tmp = 0;
		tmp = (u_int8_t)(vm_field_memory->field[tmpPC % MEM_SIZE]);
		tmp = tmp << (i * 8);
		number = number | tmp;
		tmpPC++;
		i++;
	}
	if (type == T_IND)
		return (put_value_to_arg(vm_field_memory, number, DIR_SIZE, T_DIR));
	return (number);
}

void	put_value_to_field(u_int32_t value, t_vm_field_memory *vm_field_memory, u_int64_t PC)
{
	int i;

	i = 0;
	while (i < 4)
	{
		vm_field_memory->field[(PC + i) % MEM_SIZE] = (u_int8_t)(value >> (i * 8)); 
		i++;
	}
}

// void put_value_to_register(u_int8_t *regist)
// {
// 	int i;
// 	u_int32_t number;

// 	i = 0;
// 	number = put_value_to_arg();
// 	while (i < 4)
// 	{
// //		*regist =
// 		i++;
// 	}
// }

u_int32_t	process_args(int i, u_int64_t *tmpPC,
				t_player_process *player_process, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	reg;
	u_int32_t	number;
	u_int8_t	size;

	size = vm_field_memory->op_tab[player_process->operation_code].dir_size;
	if (player_process->args[i] == T_IND)
		size = IND_SIZE;
	if (player_process->args[i] == T_REG)
	{
		reg = (u_int8_t)vm_field_memory->field[(*tmpPC) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
		{
			*tmpPC = -1;
			return (0);
		}
		number = (u_int32_t)(player_process->registers[reg * REG_SIZE - REG_SIZE]);
		*tmpPC += 1;
	}
	else
	{
		number = put_value_to_arg(vm_field_memory, *tmpPC, size, player_process->args[i]);
		*tmpPC += size;
	}
	return (number);
}

void	op11(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;
	u_int32_t	arg_value[3];
	u_int64_t	tmpPC;
	int			i;

	tmpPC = (player_process->PC + 2) % MEM_SIZE;
	regnum = vm_field_memory->field[tmpPC];
	tmpPC += 1;
	i = 1;
	while (i < 3)
	{
		arg_value[i] = process_args(i, &tmpPC, player_process, vm_field_memory);
		if (tmpPC < 0)
			break;
		i++;
	}
	if (regnum > 0 && regnum <= REG_NUMBER && tmpPC >= 0)
		put_value_to_field((*(int *)(&(player_process->registers[regnum * REG_SIZE - REG_SIZE]))),
				vm_field_memory, (player_process->PC + (arg_value[1] + arg_value[2]) %
				IDX_MOD) % MEM_SIZE);
	move_pc(game_process->op_tab, player_process);
}

// void	op10(t_game_process *game_process, t_player_process *player_process,
// 			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
// {
// 	u_int8_t	regnum;
// 	u_int32_t	arg_value[3];
// 	u_int64_t	tmpPC;
// 	int			i;

// 	tmpPC = (player_process->PC + 2) % MEM_SIZE;
// 	i = 0;
// 	while (i < 2)
// 	{
// 		arg_value[i] = process_args(i, &tmpPC, player_process, vm_field_memory);
// 		if (tmpPC < 0)
// 			break;
// 		i++;
// 	}
// 	regnum = vm_field_memory->field[tmpPC];
// 	if (regnum > 0 && regnum <= REG_NUMBER && tmpPC >= 0)
// 		put_value_to_register(player_process->registers[regnum * REG_SIZE - REG_SIZE]);
// //		 = (int32_t)(vm_field_memory->field[(player_process->PC + (arg_value[0] + arg_value[1]) %
// 																														// IDX_MOD) % MEM_SIZE])
// }

void (*operation[16])(t_game_process *game_process, t_player_process *player_process,
					  t_player_list *player_list, t_vm_field_memory *vm_field_memory) =
{
		// op01(game_process, player_process, player_list, vm_field_memory),
		// op02(game_process, player_process, player_list, vm_field_memory),
		// op03(game_process, player_process, player_list, vm_field_memory),
		// op04(game_process, player_process, player_list, vm_field_memory),
		// op05(game_process, player_process, player_list, vm_field_memory),
		// op06(game_process, player_process, player_list, vm_field_memory),
		// op07(game_process, player_process, player_list, vm_field_memory),
		// op08(game_process, player_process, player_list, vm_field_memory),
		// op09(game_process, player_process, player_list, vm_field_memory),
		// op10(game_process, player_process, player_list, vm_field_memory),
		op11/*(game_process, player_process, player_list, vm_field_memory)*/,
		op12/*(game_process, player_process, player_list, vm_field_memory)*/,
		// op13(game_process, player_process, player_list, vm_field_memory),
		// op14(game_process, player_process, player_list, vm_field_memory),
		op15/*(game_process, player_process, player_list, vm_field_memory)*/,
		op16/*(game_process, player_process, player_list, vm_field_memory)*/

};

void operation_completer(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	// player_process->registers[0] = -1;
	// player_process->registers[1] = 1;
	operation[1](game_process, player_process,
						player_list, vm_field_memory);
}