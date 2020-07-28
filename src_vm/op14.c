/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op14.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:28:36 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/27 19:29:55 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void	op14_player_process(t_player_process *player_process,
	t_vm_field_memory *vm_field_memory, int32_t *arg_value)
{
	if (player_process->args[0] == DIR_CODE)
		arg_value[0] = (int32_t)((int16_t)process_args(0,
			player_process, vm_field_memory));
	else
		arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->args[1] == DIR_CODE)
		arg_value[1] = (int32_t)((int16_t)process_args(1,
			player_process, vm_field_memory));
	else
		arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)vm_field_memory->
			field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[2] = 0;
}

void	op14(t_game_process *game_process, t_player_process *player_process,
			t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[4];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc + 2) % MEM_SIZE;
	op14_player_process(player_process, vm_field_memory, arg_value);
	player_process->reg[2] = arg_value[2];
	if ((int)arg_value[2] >= 1 && (int)arg_value[2] <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		player_process->arg_position = make_number_positive(
			(int64_t)player_process->pc +
			(int64_t)arg_value[0] + (int64_t)arg_value[1]);
		arg_value[3] = take_value_from_field(vm_field_memory,
			player_process, 4, DIR_CODE);
		put_value_to_register(&(player_process->
			registers[REG_SIZE * (arg_value[2] - 1)]),
			arg_value[3]);
		if (arg_value[3] == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}
