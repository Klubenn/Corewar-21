/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_for_args_type.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:37:56 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 22:29:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

bool	validation_while_cycle(t_game_process *game_process,
	t_player_process *player_process, t_vm_field_memory *vm_field_memory,
	u_int8_t *counter)
{
	u_int8_t	comparator;

	comparator = (game_process->op_tab)
		[player_process->operation_code].arg_types[*counter];
	if (player_process->args[*counter] == REG_CODE
		&& !(comparator & T_REG))
		return (move_pc(game_process->op_tab, player_process,
			game_process, vm_field_memory));
	else if (player_process->args[*counter] == DIR_CODE
		&& !(comparator & T_DIR))
		return (move_pc(game_process->op_tab, player_process,
			game_process, vm_field_memory));
	else if (player_process->args[*counter] == IND_CODE
		&& !(comparator & T_IND))
		return (move_pc(game_process->op_tab, player_process,
			game_process, vm_field_memory));
	else if (player_process->args[*counter] == 0
		&& (comparator))
		return (move_pc(game_process->op_tab, player_process,
			game_process, vm_field_memory));
	else
		(*counter)++;
	return (true);
}

bool	validation_before_operation_complete(t_game_process *game_process,
	t_player_process *player_process, t_vm_field_memory *vm_field_memory)
{
	u_int8_t	args_type_code;
	u_int8_t	counter;

	counter = 0;
	if (game_process->op_tab[player_process->
		operation_code].have_a_code_type_code == 0)
		return (true);
	args_type_code = (vm_field_memory->field)
		[(player_process->pc + 1) % MEM_SIZE];
	player_process->args[0] = (args_type_code & 192) >> 6;
	player_process->args[1] = (args_type_code & 48) >> 4;
	player_process->args[2] = (args_type_code & 12) >> 2;
	while (counter < game_process->op_tab
		[player_process->operation_code].args_number)
	{
		if (!(validation_while_cycle(game_process, player_process,
			vm_field_memory, &counter)))
			return (false);
	}
	return (true);
}
