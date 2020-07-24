/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_deleter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:29:30 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 22:29:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void	memory_error_cleaner(t_player_process *player_process)
{
	t_player_process *buff_player_process;

	while (player_process)
	{
		buff_player_process = player_process;
		player_process = player_process->next;
		free(buff_player_process);
	}
}

void	memory_deleter(t_player_list *player_list,
	t_vm_field_memory *vm_field_memory,
	t_game_process *game_process)
{
	t_player_list	*player_list_buff;

	while (player_list)
	{
		free(player_list->player->code);
		free(player_list->player);
		player_list_buff = player_list;
		player_list = player_list->next;
		free(player_list_buff);
	}
	if (vm_field_memory)
	{
		free(vm_field_memory->field);
		free(vm_field_memory);
	}
	if (game_process)
	{
		if (game_process->count)
			free(game_process->count);
		free(game_process);
	}
}
