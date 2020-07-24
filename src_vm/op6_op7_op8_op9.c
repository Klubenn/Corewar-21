/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op6_op7_op8_op9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 20:36:32 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 22:29:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void	op6_op7_op8_helper(t_vm_field_memory *vm_field_memory,
	t_player_process *player_process, u_int32_t *arg_value)
{
	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)vm_field_memory->
			field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[2] = 0;
	player_process->reg[2] = arg_value[2];
}

void	op6(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	op6_op7_op8_helper(vm_field_memory, player_process,
		arg_value);
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->
			registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(arg_value[0] & arg_value[1]));
		if ((arg_value[0] & arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process,
			(int32_t *)arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}

void	op7(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	op6_op7_op8_helper(vm_field_memory, player_process,
		arg_value);
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->
			registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(arg_value[0] | arg_value[1]));
		if ((arg_value[0] | arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process,
			(int32_t *)arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}

void	op8(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int32_t	arg_value[3];

	op6_op7_op8_helper(vm_field_memory, player_process,
		arg_value);
	if (((int)arg_value[2]) >= 1 && ((int)arg_value[2]) <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->
			registers[REG_SIZE * ((u_int8_t)arg_value[2] - 1)]),
			(arg_value[0] ^ arg_value[1]));
		if ((arg_value[0] ^ arg_value[1]) == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process,
			(int32_t *)arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}

void	op9(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value_2;
	int16_t	arg_value;

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc + 1) % MEM_SIZE;
	arg_value = take_value_from_field(vm_field_memory,
		player_process, 2, DIR_CODE);
	arg_value_2 = (int32_t)arg_value;
	print_operation_logs(player_process, &arg_value_2, game_process);
	if (player_process->carry == true)
	{
		player_process->pc = (u_int64_t)make_number_positive(
			(int64_t)(player_process->pc)
			+ (((int64_t)arg_value) % ((int64_t)IDX_MOD)));
	}
	else
		move_pc(game_process->op_tab, player_process,
			game_process, vm_field_memory);
}
