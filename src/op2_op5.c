/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2_op5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 20:09:38 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 22:59:06 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	op2(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[2];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[1] = (u_int8_t)vm_field_memory->
			field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[1] = 0;
	player_process->reg[1] = arg_value[1];
	if (((int)arg_value[1]) >= 1 && ((int)arg_value[1]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE
			* (arg_value[1] - 1)]), arg_value[0]);
		if (arg_value[0] == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, (int32_t *)arg_value,
			game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}

void	op3_helper(t_game_process *game_process,
	t_player_process *player_process,
	int32_t *arg_value, t_vm_field_memory *vm_field_memory)
{
	if (player_process->args[1] == REG_CODE
		&& player_process->arg_position >= 0)
	{
		if (((int)arg_value[1]) >= 1 && ((int)arg_value[1]) <= REG_NUMBER)
			put_value_to_register(&(player_process->registers[REG_SIZE
				* ((u_int8_t)arg_value[1] - 1)]),
				arg_value[0]);
		print_operation_logs(player_process, arg_value, game_process);
	}
	else if (player_process->args[1] == IND_CODE
		&& player_process->arg_position >= 0)
	{
		put_value_to_field(arg_value[0], vm_field_memory,
			(u_int64_t)make_number_positive((int64_t)player_process->pc +
				((int64_t)arg_value[1] % (int64_t)IDX_MOD)));
		print_operation_logs(player_process, arg_value, game_process);
	}
}

void	op3(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[2];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->args[1] == REG_CODE
			&& player_process->arg_position >= 0)
	{
		arg_value[1] = (u_int8_t)vm_field_memory->
			field[(player_process->arg_position) % MEM_SIZE];
		player_process->reg[1] = arg_value[1];
	}
	else if (player_process->args[1] == IND_CODE
				&& player_process->arg_position >= 0)
		arg_value[1] = take_value_from_field(vm_field_memory,
			player_process, 2, DIR_CODE);
	op3_helper(game_process, player_process,
		arg_value, vm_field_memory);
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}

void	op4(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	op4_op5_helper(arg_value, player_process,
		vm_field_memory);
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->registers[REG_SIZE
			* ((u_int8_t)arg_value[2] - 1)]),
			(u_int32_t)(arg_value[0] + arg_value[1]));
		if ((arg_value[0] + arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}

void	op5(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	op4_op5_helper(arg_value, player_process,
		vm_field_memory);
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->
			registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			arg_value[0] - arg_value[1]);
		if ((arg_value[0] - arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab,
		player_process, game_process, vm_field_memory);
}
