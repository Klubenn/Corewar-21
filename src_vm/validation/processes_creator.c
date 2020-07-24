/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_creator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:36:48 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_vm/corewar.h"

void				player_process_initializer(t_player_process
	**player_process, t_vm_field_memory *vm_field_memory,
	t_game_process *game_process, t_player_list *player_list)
{
	int		counter;

	counter = REG_SIZE - 1;
	if (!((*player_process) = (t_player_process *)
		ft_memalloc(sizeof(t_player_process))))
	{
		memory_error_cleaner(game_process->beginner);
		memory_deleter(game_process->begin_list, vm_field_memory, game_process);
		perror("Error");
		exit(1);
	}
	while (counter > 0)
	{
		(*player_process)->registers[counter] = (unsigned char)(255);
		counter--;
	}
	(*player_process)->registers[counter] =
		(unsigned char)(-1 * (player_list->position));
	(*player_process)->next = 0;
	(*player_process)->ident =
		(u_int64_t)(*((int *)(&((*player_process)->registers[0])))) * (-1);
	(*player_process)->carry = false;
	(*player_process)->pc =
		(MEM_SIZE / game_process->divider) * (player_list->position - 1);
}

void				create_process_helper(t_player_process **player_process,
	t_vm_field_memory *vm_field_memory, t_game_process *game_process,
	t_player_list *player_list)
{
	player_process_initializer(player_process, vm_field_memory,
		game_process, player_list);
	(*player_process)->operation_code = vm_field_memory->field
		[(*player_process)->pc];
	(*player_process)->cycles_to_wait = (vm_field_memory->op_tab)
		[(*player_process)->operation_code].cycles_before_complete;
}

t_player_process	*create_processes(t_player_list *player_list,
	int divider, t_vm_field_memory *vm_field_memory,
	t_game_process *game_process)
{
	t_player_process	*player_process;

	while (player_list->next)
		player_list = player_list->next;
	game_process->divider = divider;
	while (player_list)
	{
		if (player_list->next == 0)
		{
			create_process_helper(&player_process, vm_field_memory,
				game_process, player_list);
			game_process->beginner = player_process;
			player_process->prev = 0;
		}
		else
		{
			create_process_helper(&(player_process->next), vm_field_memory,
				game_process, player_list);
			player_process->next->prev = player_process;
			player_process = player_process->next;
		}
		player_list = player_list->prev;
	}
	return (game_process->beginner);
}
