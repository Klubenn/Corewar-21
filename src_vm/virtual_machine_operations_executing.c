/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_operations_executing.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:36:37 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 22:29:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void				op_code_and_cycles_to_wait_definer(t_player_process
	*player_process, t_vm_field_memory *vm_field_memory,
	t_game_process *game_process)
{
	player_process->operation_code = vm_field_memory->
			field[player_process->pc];
	if ((1 <= player_process->operation_code &&
		player_process->operation_code <= 16))
		player_process->cycles_to_wait =
		(game_process->op_tab)[player_process->
		operation_code].cycles_before_complete - 1;
	else
		player_process->pc = (player_process->pc + 1) % MEM_SIZE;
}

t_player_process	*players_operations_executing(t_game_process *game_process,
	t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	game_process->player_list = player_list;
	while (player_process)
	{
		if (player_process->cycles_to_wait == 1)
		{
			if (validation_before_operation_complete(game_process,
				player_process, vm_field_memory))
				operation_completer(game_process, player_process,
				vm_field_memory);
			player_process->args[0] = 0;
			player_process->args[1] = 0;
			player_process->args[2] = 0;
			player_process->cycles_to_wait -= 1;
		}
		else if (player_process->cycles_to_wait == 0)
			op_code_and_cycles_to_wait_definer(player_process,
			vm_field_memory, game_process);
		else
			player_process->cycles_to_wait -= 1;
		player_process = player_process->next;
	}
	return (game_process->beginner);
}
