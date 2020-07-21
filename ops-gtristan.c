#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "corewar.h"
#include "libft/libft.h"
#include <fcntl.h>
#include "op.h"
#include <time.h>

//todo поменять считывание операции после перемещения

void print_args(t_player_process *player_process, int32_t *arg_value, t_game_process *game_process)
{
	int i;

	i = 0;
	if (game_process->op_tab[player_process->operation_code].have_a_code_type_code != 0)
	{
		while (i < game_process->op_tab[player_process->operation_code].args_number)
		{
			if (player_process->args[i] == 1 &&
				(game_process->op_tab[player_process->operation_code].arg_types[i]
					| T_REG) == T_REG)
				ft_printf(" r%d", (int32_t)player_process->reg[i]);
			else
				ft_printf(" %d", (int32_t)arg_value[i]);
			i++;
		}
	}
	else
		ft_printf(" %d", *arg_value);
	if (ft_strcmp(game_process->op_tab[player_process->operation_code].name, "fork") == 0 ||
			ft_strcmp(game_process->op_tab[player_process->operation_code].name, "lfork") == 0)
			ft_printf(" (%llu)", player_process->PC);
	if (ft_strcmp(game_process->op_tab[player_process->operation_code].name, "zjmp") == 0)
	{
		if (player_process->carry == true)
			ft_printf(" OK");
		else
			ft_printf(" FAILED");
	}
	if (ft_strcmp(game_process->op_tab[player_process->operation_code].name, "sti") == 0)
	{
		ft_printf("\n       | -> store to %d + %d = %d (with pc and mod %d)",
			arg_value[1], arg_value[2], arg_value[1] + arg_value[2], (int32_t)((int64_t)player_process->PC +
				(int64_t)(((int64_t)arg_value[1] + (int64_t)arg_value[2]) % (int64_t)IDX_MOD)));
	}
	if (ft_strcmp(game_process->op_tab[player_process->operation_code].name, "ldi") == 0)
	{
		ft_printf("\n       | -> load from %d + %d = %d (with pc and mod %d)",
			arg_value[0], arg_value[1], arg_value[0] + arg_value[1], (int32_t)((int64_t)player_process->PC +
			(((int64_t)arg_value[0] + (int64_t)arg_value[1]) % (int64_t)IDX_MOD)));
	}
	if (ft_strcmp(game_process->op_tab[player_process->operation_code].name, "lldi") == 0)
	{
		ft_printf("\n       | -> load from %d + %d = %d (with pc %d)",
			arg_value[0], arg_value[1], arg_value[0] + arg_value[1], (int32_t)((int64_t)player_process->PC +
				(int64_t)arg_value[0] + (int64_t)arg_value[1]));
	}
	ft_printf("\n");
}

void print_operation_logs(t_player_process *player_process, int32_t	*arg_value, t_game_process *game_process)
{
	if ((game_process->flag_v) & 4)
	{
		if (ft_strcmp(game_process->op_tab[player_process->operation_code].name, "fork") == 0 ||
			ft_strcmp(game_process->op_tab[player_process->operation_code].name, "lfork") == 0)
			ft_printf("P %4.llu | %s",
				player_process->parent, game_process->op_tab[player_process->operation_code].name);
		else
			ft_printf("P %4.llu | %s",
				player_process->ident, game_process->op_tab[player_process->operation_code].name);
		print_args(player_process, arg_value, game_process);
	}
}

int32_t make_number_positive(int64_t number)
{
	while (number < 0)
		number += MEM_SIZE;
	return ((int32_t)(number % MEM_SIZE));
}

int32_t	take_value_from_field(t_vm_field_memory *vm_field_memory,
			t_player_process *player_process, int size, u_int8_t type)
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
	if (i == 2)
		number = (int32_t)(int16_t)number;
	if (type == IND_CODE)
	{
		i = player_process->arg_position;
		if (vm_field_memory->modulo == false)
			player_process->arg_position = make_number_positive(((int64_t)number % (int64_t)IDX_MOD)
				+ (int64_t)player_process->PC);
		else
			player_process->arg_position = make_number_positive((int64_t)number
				+ (int64_t)player_process->PC);
		number = take_value_from_field(vm_field_memory, player_process, DIR_SIZE, DIR_CODE);
		player_process->arg_position = i;
		return (number);
	}
	return (number);
}

void	op1(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t arg;
	bool flag;

	flag = false;
	player_process->arg_position = (player_process->PC + 1) % MEM_SIZE;
	vm_field_memory->modulo = false;
	arg = (int32_t)take_value_from_field(vm_field_memory, player_process,
		(int)(game_process->op_tab[player_process->operation_code].dir_size),
			(u_int8_t)DIR_CODE);
	while (player_list)
	{
		if (arg == (-1 * player_list->position))
		{
			// player_list->player->last_live_cycle_number = game_process->cycle_number;
			game_process->last_live_player = player_list;
			// player_process->live_counter_valid += 1;
			flag = true;
			break ;
		}
		player_list = player_list->next;
	}
	player_process->live_counter += (u_int64_t)1;
	player_process->last_live_cycle_number = game_process->cycle_number;
	print_operation_logs(player_process, &arg, game_process);
	if ((game_process->flag_v & 1) && flag == true)
				ft_printf("Player %d (%s) is said to be alive\n",
					player_list->position, player_list->player->player_header.prog_name);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// print_operation_logs(player_process, &arg, game_process);
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
	// ft_printf("%u\n", *((int *)&(vm_field_memory->field[PC])));
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
	if (player_process->arg_position < 0)
		return (0);
	if (player_process->args[i] == REG_CODE)
	{
		reg = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
		{
			player_process->arg_position = -1;
			return (0);
		}
		number = *(int32_t *)(&(player_process->registers[reg * REG_SIZE - REG_SIZE]));
		player_process->reg[i] = reg;
		player_process->arg_position += 1;
	}
	else
		number = take_value_from_field(vm_field_memory, player_process, size, player_process->args[i]);
	return (number);
}

void op2(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[2];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[1] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[1] = 0;
	player_process->reg[1] = arg_value[1];
	if (((int)arg_value[1]) >= 1 && ((int)arg_value[1]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * (arg_value[1] - 1)]),
			arg_value[0]);
		if (arg_value[0] == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	}
	// print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// print_operation_logs(player_process, (int32_t *)(arg_value), game_process);
}

void op3(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[2];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->args[1] == REG_CODE
			&& player_process->arg_position >= 0)
	{
		arg_value[1] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
		player_process->reg[1] = arg_value[1];
	}
	else if (player_process->args[1] == IND_CODE
				&& player_process->arg_position >= 0)
		arg_value[1] = take_value_from_field(vm_field_memory, player_process, 2, DIR_CODE);
	// arg_value[0] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	// arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->args[1] == REG_CODE
		&& player_process->arg_position >= 0)
	{
		if (((int)arg_value[1]) >= 1 && ((int)arg_value[1]) <= REG_NUMBER)
			put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[1] - 1)]),
				arg_value[0]);
		print_operation_logs(player_process, arg_value, game_process);
	}
	else if (player_process->args[1] == IND_CODE
		&& player_process->arg_position >= 0)
	{
		put_value_to_field(arg_value[0], vm_field_memory,
			(u_int64_t)make_number_positive((int64_t)player_process->PC +
				((int64_t)arg_value[1] % (int64_t)IDX_MOD)));
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// print_operation_logs(player_process, arg_value, game_process);
	// ft_printf("%d\n", *((int *)(&(vm_field_memory->field[511]))));
}

void op4(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)(vm_field_memory->field[(player_process->arg_position) % MEM_SIZE]);
	else
		arg_value[2] = 0;
	player_process->reg[2] = arg_value[2];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(u_int32_t)(arg_value[0] + arg_value[1]));
		if ((arg_value[0] + arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, arg_value, game_process);
	}
	// print_operation_logs(player_process, arg_value, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// print_operation_logs(player_process, arg_value, game_process);
	// ft_printf("%d\n", *((int *)(&(player_process->registers[8]))));
}

void op5(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[2] = 0;
	player_process->reg[2] = arg_value[2];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			arg_value[0] - arg_value[1]);
		if ((arg_value[0] - arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, arg_value, game_process);
	}
	// print_operation_logs(player_process, arg_value, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// print_operation_logs(player_process, arg_value, game_process);
	// ft_printf("%d\n", *((int *)(&(player_process->registers[12]))));
}

void op6(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[2] = 0;
	player_process->reg[2] = arg_value[2];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(arg_value[0] & arg_value[1]));
		if ((arg_value[0] & arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	}
	// print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// ft_printf("%d\n", *((int *)(&(player_process->registers[12]))));
}

void op7(t_game_process *game_process, t_player_process *player_process,
		 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[2] = 0;
	player_process->reg[2] = arg_value[2];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(arg_value[0] | arg_value[1]));
		if ((arg_value[0] | arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	}
	// print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// ft_printf("%d\n", *((int *)(&(player_process->registers[12]))));
}

void op8(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[2] = 0;
	player_process->reg[2] = arg_value[2];
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(arg_value[0] ^ arg_value[1]));
		if ((arg_value[0] ^ arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	}
	// print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// print_operation_logs(player_process, (int32_t *)arg_value, game_process);
	// ft_printf("%d\n", *((int *)(&(player_process->registers[12]))));
}

void op9(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value_2;
	int16_t	arg_value;

	vm_field_memory->modulo = false;
	// ft_printf("%d\n", (int)(player_process->PC));
	player_process->arg_position = (player_process->PC + 1) % MEM_SIZE;
	arg_value =	take_value_from_field(vm_field_memory, player_process, 2, DIR_CODE);
	arg_value_2 = (int32_t)arg_value;
	print_operation_logs(player_process, &arg_value_2, game_process);
	if (player_process->carry == true)
	{
		player_process->PC = (u_int64_t)make_number_positive((int64_t)(player_process->PC)
			+ (((int64_t)arg_value) % ((int64_t)IDX_MOD)));
	}
	else
	{
		move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	}
	// arg_value_2 = (int32_t)arg_value;
	// print_operation_logs(player_process, &arg_value_2, game_process);
	// ft_printf("%d\n", (int)(player_process->PC));
}

void	op10(t_game_process *game_process, t_player_process *player_process,
 			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;
	int32_t		arg_value[2];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	if (player_process->args[0] == DIR_CODE)
		arg_value[0] = (int32_t)((int16_t)process_args(0, player_process, vm_field_memory));
	else
		arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->args[1] == DIR_CODE)
		arg_value[1] = (int32_t)((int16_t)process_args(1, player_process, vm_field_memory));
	else
		arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		regnum = vm_field_memory->field[player_process->arg_position];
	else
		regnum = 0;
	player_process->reg[2] = regnum;
	if (regnum > 0 && regnum <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		player_process->arg_position = make_number_positive((int64_t)player_process->PC +
			(((int64_t)arg_value[0] + (int64_t)arg_value[1]) % (int64_t)IDX_MOD));
		put_value_to_register(&player_process->registers[regnum * REG_SIZE - REG_SIZE],
				take_value_from_field(vm_field_memory, player_process, REG_SIZE, DIR_CODE));
		print_operation_logs(player_process, arg_value, game_process);
	}
	// print_operation_logs(player_process, arg_value, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
}

void	op11(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->args[1] == DIR_CODE)
		arg_value[1] = (int32_t)((int16_t)process_args(1, player_process, vm_field_memory));
	else
		arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->args[2] == DIR_CODE)
		arg_value[2] = (int32_t)((int16_t)process_args(2, player_process, vm_field_memory));
	else
		arg_value[2] = process_args(2, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
	{
		put_value_to_field(arg_value[0], vm_field_memory,
						   make_number_positive((int64_t) player_process->PC +
												(((int64_t) arg_value[1] + (int64_t) arg_value[2]) %
												 (int64_t) IDX_MOD)));
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
}

void	op12(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	t_player_process *new;
	int64_t			bias;

	vm_field_memory->modulo = false;
	new = game_process->beginner;
	if (!(new->prev = (t_player_process *)ft_memalloc(sizeof(t_player_process))))
	{
		memory_error_cleaner(game_process->beginner);
		memory_deleter(game_process->begin_list, vm_field_memory, game_process);
		perror("Error");
		exit(1);
	}
	ft_memcpy(new->prev, player_process, sizeof(t_player_process));
	// ft_printf("%d\n", (*((short *)(&(vm_field_memory->field[player_process->PC
	// 	+ 1])))));
	player_process->arg_position = (player_process->PC + 1) % MEM_SIZE;
	bias = (((int64_t)(int16_t)(take_value_from_field(vm_field_memory, player_process, 2, DIR_CODE))) % ((int64_t)IDX_MOD));
	new->prev->PC = (u_int64_t)make_number_positive(bias + (int64_t)(player_process->PC));
	new->prev->cycles_to_wait = 0;
	new->prev->next = new;
	new->prev->prev = NULL;
	game_process->beginner = new->prev;
	new->prev->ident = game_process->process_numbers + 1;
	new->prev->parent = player_process->ident;
	new->prev->live_counter = 0;
	new->prev->args[0] = 0;
	new->prev->args[1] = 0;
	new->prev->args[2] = 0;
	game_process->process_numbers += 1;
	// player_process->PC = (player_process->PC + 3) % MEM_SIZE;
	print_operation_logs(new->prev, ((int32_t *)(&bias)), game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
}

void op13(t_game_process *game_process, t_player_process *player_process,
			t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[2];

	vm_field_memory->modulo = true;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	if (player_process->args[0] == DIR_CODE)
		arg_value[0] = (int32_t)process_args(0, player_process, vm_field_memory);
	else
		arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[1] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[1] = 0;
	player_process->reg[1] = arg_value[1];
	if ((int)arg_value[1] >= 1 && (int)arg_value[1] <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE * (arg_value[1] - 1)]), arg_value[0]);
		if (arg_value[0] == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, arg_value, game_process);
	}
	// print_operation_logs(player_process, arg_value, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// ft_printf("%d\n", *((int *)(&(player_process->registers[8]))));
}

void op14(t_game_process *game_process, t_player_process *player_process,
			t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[4];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->PC + 2) % MEM_SIZE;
	if (player_process->args[0] == DIR_CODE)
		arg_value[0] = (int32_t)((int16_t)process_args(0, player_process, vm_field_memory));
	else
		arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->args[1] == DIR_CODE)
		arg_value[1] = (int32_t)((int16_t)process_args(1, player_process, vm_field_memory));
	else
		arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)vm_field_memory->field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[2] = 0;
	player_process->reg[2] = arg_value[2];
	if ((int)arg_value[2] >= 1 && (int)arg_value[2] <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		player_process->arg_position = make_number_positive((int64_t)player_process->PC +
			(int64_t)arg_value[0] + (int64_t)arg_value[1]);
		arg_value[3] = take_value_from_field(vm_field_memory, player_process, 4, DIR_CODE);
		put_value_to_register(&(player_process->registers[REG_SIZE * (arg_value[2] - 1)]),
			arg_value[3]);
		if (arg_value[0] == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
}

void	op15(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	t_player_process *new;
	int64_t			bias;

	// new = player_process;
	new = game_process->beginner;
	// while (new->prev)
	// 	new = new->prev;
	// ft_printf("%llu\n", loop);
	vm_field_memory->modulo = false;
	if (!(new->prev = (t_player_process *)ft_memalloc(sizeof(t_player_process))))
	{
		memory_error_cleaner(game_process->beginner);
		memory_deleter(game_process->begin_list, vm_field_memory, game_process);
		perror("Error");
		exit(1);
	}
	ft_memcpy(new->prev, player_process, sizeof(t_player_process));
	// ft_printf("%hd\n", (*((int16_t *)(&(vm_field_memory->field[player_process->PC + 1])))));
	player_process->arg_position = (player_process->PC + 1) % MEM_SIZE;
	bias = ((int64_t)(int16_t)(take_value_from_field(vm_field_memory, player_process, 2, DIR_CODE)));
	new->prev->PC = (u_int64_t)make_number_positive(bias + (int64_t)(player_process->PC));
	new->prev->cycles_to_wait = 0;
	new->prev->next = new;
	new->prev->prev = NULL;
	game_process->beginner = new->prev;
	new->prev->ident = game_process->process_numbers + 1;
	new->prev->parent = player_process->ident;
	new->prev->live_counter = 0;
	new->prev->args[0] = 0;
	new->prev->args[1] = 0;
	new->prev->args[2] = 0;
	game_process->process_numbers += 1;
	print_operation_logs(new->prev, ((int32_t *)(&bias)), game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
	// player_process->PC = (player_process->PC + 3) % MEM_SIZE;
	// print_operation_logs(new->prev, ((int32_t *)(&bias)), game_process);
}

void 	op16(t_game_process *game_process, t_player_process *player_process,
			 t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;
	u_int8_t	args_type_code;

	regnum = vm_field_memory->field[(player_process->PC + 2) % MEM_SIZE];
	player_process->reg[0] = (int32_t)regnum;
	if (regnum > 0 &&
		regnum <= REG_NUMBER &&
			game_process->flag_a
			/*&& (32 <= (char)player_process->registers[regnum * REG_SIZE - REG_SIZE]
					&& (char)player_process->registers[regnum * REG_SIZE - REG_SIZE] < 127)*/)
		ft_printf("Aff: %c\n", player_process->registers[regnum * REG_SIZE - REG_SIZE]);
	// print_operation_logs(player_process, 0, game_process);
	move_pc(game_process->op_tab, player_process, game_process, vm_field_memory);
}

void (*operation[17])(t_game_process *game_process, t_player_process *player_process,
					  t_player_list *player_list, t_vm_field_memory *vm_field_memory) =
{
		0,
		op1,
		op2,
		op3,
		op4,
		op5,
		op6,
		op7,
		op8,
		op9,
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
		op13,
		op14,
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
	// ft_printf("%x\n", *ex);
	// vm_field_memory->field[73] = 0xff;
	// player_process->carry = true;
	operation[game_process->op_tab[player_process->operation_code].bytecode_operation](game_process, player_process,
						player_list, vm_field_memory);
}