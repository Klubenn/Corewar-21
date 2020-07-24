/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_deleter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:41:11 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 22:29:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void	delete_process(t_player_process *player_process,
	t_player_process **player_process_begin)
{
	if (player_process->prev != 0 && player_process->next != 0)
	{
		player_process->prev->next = player_process->next;
		player_process->next->prev = player_process->prev;
		free(player_process);
	}
	else if (player_process->prev != 0 && player_process->next == 0)
	{
		player_process->prev->next = 0;
		free(player_process);
	}
	else if (player_process->prev == 0 && player_process->next != 0)
	{
		player_process->next->prev = 0;
		*player_process_begin = player_process->next;
		free(player_process);
	}
	else if (player_process->prev == 0 && player_process->next == 0)
	{
		*player_process_begin = 0;
		free(player_process);
	}
}

void	delete_process_1(t_player_process **player_process_begin,
	t_player_process **player_process, u_int64_t *live_counter,
	t_game_process *game_process)
{
	t_player_process	*player_process_buff;

	player_process_buff = *player_process;
	if (game_process->beginner == player_process_buff)
		game_process->beginner = (*player_process)->next;
	*live_counter = *live_counter + (*player_process)->live_counter;
	*player_process = (*player_process)->next;
	if (game_process->flag_v & 8)
		ft_printf("Process %llu hasn't lived for %llu cycles (CTD %d)\n",
			player_process_buff->ident,
				game_process->cycle_number -
					player_process_buff->last_live_cycle_number,
						(int32_t)game_process->cycle_to_die);
	delete_process(player_process_buff, player_process_begin);
}

void	deleter_and_live_counter(t_game_process *game_process,
	u_int64_t *live_counter, t_player_process **player_process,
	t_player_process **player_process_begin)
{
	if (((*player_process)->live_counter == 0 &&
		(int64_t)(game_process->cycle_number -
			(*player_process)->last_live_cycle_number)
			>= game_process->cycle_to_die)
			|| game_process->cycle_to_die <= 0)
		delete_process_1(player_process_begin,
			player_process, live_counter, game_process);
	else
	{
		*live_counter = *live_counter + (*player_process)->live_counter;
		(*player_process)->live_counter = 0;
		(*player_process) = (*player_process)->next;
	}
}
