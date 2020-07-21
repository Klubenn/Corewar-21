/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_deleter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 15:29:30 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/21 21:51:37 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include "corewar.h"
#include "libft/libft.h"
#include <fcntl.h>
#include "op.h"

// void player_deleter(t_player *player)
// {
	
// }

void memory_error_cleaner(t_player_process *player_process)
{
	t_player_process *buff_player_process;

	while (player_process)
	{
		buff_player_process = player_process;
		player_process = player_process->next;
		free(buff_player_process);
	}
}

void memory_deleter(t_player_list *player_list, t_vm_field_memory *vm_field_memory,
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
		free(game_process);
}