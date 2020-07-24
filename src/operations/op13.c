/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op13.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:25:50 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	op13_helper(int32_t *arg_value, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	vm_field_memory->modulo = true;
	player_process->arg_position = (player_process->pc + 2) % MEM_SIZE;
	if (player_process->args[0] == DIR_CODE)
		arg_value[0] = (int32_t)process_args(0,
			player_process, vm_field_memory);
	else
		arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		arg_value[1] = (u_int8_t)vm_field_memory->
			field[(player_process->arg_position) % MEM_SIZE];
	else
		arg_value[1] = 0;
	player_process->reg[1] = arg_value[1];
}

void	op13(t_game_process *game_process,
	t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[2];

	op13_helper(arg_value, player_process, vm_field_memory);
	if ((int)arg_value[1] >= 1 && (int)arg_value[1] <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		put_value_to_register(&(player_process->
			registers[REG_SIZE * (arg_value[1] - 1)]), arg_value[0]);
		if (arg_value[0] == 0)
			player_process->carry = true;
		else
			player_process->carry = false;
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}
