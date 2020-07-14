#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "corewar.h"
#include "libft/libft.h"
#include <fcntl.h>
#include "op.h"

// void	op1(t_game_process *game_process, t_player_process *player_process,
// 			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
// {
// 	int32_t arg;

// 	player_process->arg_position = (player_process->PC + 1) % MEM_SIZE;
// 	arg = (int32_t)take_value_from_field(vm_field_memory, player_process,
// 		(int)(game_process->op_tab[player_process->operation_code].dir_size), (u_int8_t)DIR_CODE);
// 	while (player_list)
// 	{
// 		if (arg == (-1 * player_list->position))
// 			player_list->player->last_live_cycle_number = game_process->cycle_number;
// 		player_list = player_list->next;
// 	}
// 	player_process->live_counter += 1;
// 	player_process->last_live_cycle_number = game_process->cycle_number;
// 	move_pc(game_process->op_tab, player_process);
// }

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
	new->prev = (t_player_process *)ft_memalloc(sizeof(t_player_process));
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
	new->prev = (t_player_process *)ft_memalloc(sizeof(t_player_process));
	ft_memcpy(new->prev, player_process, sizeof(t_player_process));
	new->prev->PC = (new->prev->PC + *((short *)(&(vm_field_memory->field[player_process->PC + 1])))) % MEM_SIZE;
	new->prev->operation_code = vm_field_memory->field[new->prev->PC];
	new->prev->next = new;
	new->prev->prev = NULL;
	player_process->PC += 3;
}

int32_t make_number_positive(int32_t number)
{
	while (number < 0)
		number += MEM_SIZE;
	return (number);
}

int32_t	take_value_from_field(t_vm_field_memory *vm_field_memory,
			t_player_process *player_process, int size, u_int8_t type)//todo previous name put_value_to_arg
{
	int32_t number;
	u_int32_t tmp;
	int32_t i;

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
		player_process->arg_position = make_number_positive(number + player_process->PC);
		number = take_value_from_field(vm_field_memory, player_process, DIR_SIZE, DIR_CODE);
		player_process->arg_position = i + IND_SIZE;
		return (number);
	}
	return (number);
}

void	op1(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t arg;

	player_process->arg_position = (player_process->PC + 1) % MEM_SIZE;
	arg = (int32_t)take_value_from_field(vm_field_memory, player_process,
		(int)(game_process->op_tab[player_process->operation_code].dir_size),
			(u_int8_t)DIR_CODE);
	while (player_list)
	{
		if (arg == (-1 * player_list->position))
			player_list->player->last_live_cycle_number = game_process->cycle_number;
		player_list = player_list->next;
	}
	player_process->live_counter += 1;
	player_process->last_live_cycle_number = game_process->cycle_number;
	move_pc(game_process->op_tab, player_process);
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

int32_t	process_args(int i,	t_player_process *player_process, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	reg;
	int32_t	number;
	u_int8_t	size;

	size = (player_process->args[i] == IND_CODE) ? IND_SIZE : vm_field_memory->op_tab[player_process->operation_code].dir_size;
	if (player_process->args[i] == REG_CODE)
	{
		reg = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
		{
			player_process->arg_position = -1;
			return (0);
		}
		number = *(int32_t *)(&(player_process->registers[reg * REG_SIZE - REG_SIZE]));
		player_process->arg_position += 1;
	}
	else
	{
		number = take_value_from_field(vm_field_memory, player_process, size, player_process->args[i]);
		// player_process->arg_position += size;
	}
	return (number);
}

void op2(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[2];

	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	if (((int)arg_value[1]) >= 1 && ((int)arg_value[1]) <= REG_NUMBER)
	{
		*((u_int32_t *)&(player_process->registers[REG_SIZE * (arg_value[1] - 1)])) = arg_value[0];
		if (arg_value[0] == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
	}
	move_pc(game_process->op_tab, player_process);
}

void op3(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[2];

	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->args[1] == REG_CODE)
		arg_value[1] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	else if (player_process->args[1] == IND_CODE)
		arg_value[1] = take_value_from_field(vm_field_memory, player_process, 2, DIR_CODE);
	// arg_value[0] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	// arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->args[1] == REG_CODE)
	{
		if (((int)arg_value[1]) >= 1 && ((int)arg_value[1]) <= REG_NUMBER)
			put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[1] - 1)]),
				arg_value[0]);
	}
	else if (player_process->args[1] == IND_CODE)
		put_value_to_field(arg_value[0], vm_field_memory, (player_process->PC + (make_number_positive(arg_value[1]) % IDX_MOD)) % MEM_SIZE);
	move_pc(game_process->op_tab, player_process);
	printf("%d\n", *((int *)(&(vm_field_memory->field[10]))));
}

void op4(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			arg_value[0] + arg_value[1]);
		if ((arg_value[0] + arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
	}
	move_pc(game_process->op_tab, player_process);
	printf("%d\n", *((int *)(&(player_process->registers[8]))));
}

void op5(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			arg_value[0] - arg_value[1]);
		if ((arg_value[0] - arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
	}
	move_pc(game_process->op_tab, player_process);
	printf("%d\n", *((int *)(&(player_process->registers[8]))));
}

void op6(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(arg_value[0] & arg_value[1]));
		if ((arg_value[0] & arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
	}
	move_pc(game_process->op_tab, player_process);
	printf("%d\n", *((int *)(&(player_process->registers[8]))));
}

void op7(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)//todo всюду по аналогии с моими операциями
			 // в цикле надо запустить получение аргументов, т.к. при невалидном регистре arg_position становится меньше нуля
			 // и из цикла нужно делать break, а потом проверить это условие при выполнении самой операции
{
	u_int32_t	arg_value[3];

	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(arg_value[0] ^ arg_value[1]));
		if ((arg_value[0] ^ arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
	}
	move_pc(game_process->op_tab, player_process);
	printf("%d\n", *((int *)(&(player_process->registers[8]))));
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
		put_value_to_field(arg_value[0], vm_field_memory,
			(player_process->PC + (make_number_positive(arg_value[1]
			+ arg_value[2])) % IDX_MOD) % MEM_SIZE);
	move_pc(game_process->op_tab, player_process);
}

void	op10(t_game_process *game_process, t_player_process *player_process,
 			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;
	int32_t		arg_value[3];
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
		player_process->arg_position = player_process->PC + make_number_positive(arg_value[0] + arg_value[1]) % IDX_MOD;
		put_value_to_register(&player_process->registers[regnum * REG_SIZE - REG_SIZE],
				take_value_from_field(vm_field_memory, player_process, REG_SIZE, DIR_CODE));
	}
	move_pc(game_process->op_tab, player_process);
}

void (*operation[16])(t_game_process *game_process, t_player_process *player_process,
					  t_player_list *player_list, t_vm_field_memory *vm_field_memory) =
{
		op1,
		op2,
		op3,
		op4,
		op5,
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
	// vm_field_memory->field[73] = 0xff;
	operation[4](game_process, player_process,
						player_list, vm_field_memory);
}