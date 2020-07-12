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

u_int32_t	take_value_from_field(t_vm_field_memory *vm_field_memory,
			t_player_process *player_process, int size, u_int8_t type)//todo previous name put_value_to_arg
{
	u_int32_t number;
	u_int32_t tmp;
	u_int32_t i;

	number = 0;
	i = 0;
	while(i < size)
	{
		tmp = 0;
		tmp = (u_int8_t)(vm_field_memory->field[player_process->arg_position % MEM_SIZE]);
		tmp = tmp << ((size - 1 - i) * 8);
		number = number | tmp;
		(player_process->arg_position)++;
		i++;
	}
	if (type == IND_CODE)
	{
		i = player_process->arg_position;
		player_process->arg_position = number + player_process->PC;
		number = take_value_from_field(vm_field_memory, player_process, DIR_SIZE, DIR_CODE);
		player_process->arg_position = i + IND_SIZE;
		return (number);
	}
	return (number);
}

void	put_value_to_field(u_int32_t value, t_vm_field_memory *vm_field_memory, u_int64_t PC)
{
	int i;

	i = 0;
	while (i < 4)
	{
		vm_field_memory->field[(PC + i) % MEM_SIZE] = (u_int8_t)(value >> ((3 - i) * 8));
		i++;
	}
	// printf("%u\n", *((int *)&(vm_field_memory->field[PC])));
}

void	put_value_to_register(u_int8_t *regist, u_int32_t value)
 {
 	int i;

 	i = 0;
 	while (i < 4)
 	{
 		*regist = (u_int8_t)(value >> (8 * i));
 		i++;
 		regist++;
 	}
 }

u_int32_t	process_args(int i,	t_player_process *player_process, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	reg;
	u_int32_t	number;
	u_int8_t	size;

	size = (player_process->args[i] == T_IND) ? IND_SIZE : vm_field_memory->op_tab[player_process->operation_code].dir_size;
	if (player_process->args[i] == T_REG)
	{
		reg = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
		{
			player_process->arg_position = -1;
			return (0);
		}
		number = *(u_int32_t *)(&(player_process->registers[reg * REG_SIZE - REG_SIZE]));
		player_process->arg_position += 1;
	}
	else
	{
		number = take_value_from_field(vm_field_memory, player_process, size, player_process->args[i]);
		// player_process->arg_position += size;
	}
	return (number);
}

void	op11(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];
	int			i;

	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	i = 0;
	while (i < 3)
	{
		arg_value[i] = process_args(i, player_process, vm_field_memory);
		if (player_process->arg_position < 0)
			break;
		i++;
	}
	if (player_process->arg_position >= 0)
		put_value_to_field(arg_value[0], vm_field_memory, (player_process->PC + (arg_value[1] + arg_value[2]) %
				IDX_MOD) % MEM_SIZE);
	move_pc(game_process->op_tab, player_process);
}

void	op10(t_game_process *game_process, t_player_process *player_process,
 			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;
	u_int32_t	arg_value[3];
	int			i;

	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	i = 0;
	while (i < 2)
	{
		arg_value[i] = process_args(i, player_process, vm_field_memory);
		if (player_process->arg_position < 0)
			break;
		i++;
	}
	regnum = vm_field_memory->field[player_process->arg_position];
	if (regnum > 0 && regnum <= REG_NUMBER && player_process->arg_position >= 0)
	{
		player_process->arg_position = player_process->PC + (arg_value[0] + arg_value[1]) % IDX_MOD;
		put_value_to_register(&player_process->registers[regnum * REG_SIZE - REG_SIZE],
				take_value_from_field(vm_field_memory, player_process, REG_SIZE, DIR_CODE));
	}
	move_pc(game_process->op_tab, player_process);
}

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
		op10,
		op11,
		op12,
		// op13(game_process, player_process, player_list, vm_field_memory),
		// op14(game_process, player_process, player_list, vm_field_memory),
		op15,
		op16

};

void operation_completer(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int *ex;
	// player_process->registers[0] = COREWAR_EXEC_MAGIC;
	// player_process->registers[0] = 171;
	// player_process->registers[1] = 205;
	// player_process->registers[2] = 239;
	// player_process->registers[3] = 16;
	// ex = (int *)(player_process->registers);
	// *ex = COREWAR_EXEC_MAGIC;
	// player_process->registers[0] = 0x00;
	// player_process->registers[1] = 0xea;
	// player_process->registers[2] = 0x83;
	// player_process->registers[3] = 0xf3;
	// printf("%x\n", *ex);
	vm_field_memory->field[73] = 0xff;
	operation[1](game_process, player_process,
						player_list, vm_field_memory);
}