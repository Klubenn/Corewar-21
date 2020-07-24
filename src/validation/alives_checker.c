/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alives_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:44:18 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_alives(t_game_process *game_process,
	t_player_process **player_process_begin)
{
	u_int64_t			live_counter;
	t_player_process	*player_process;

	live_counter = 0;
	player_process = *player_process_begin;
	while (player_process)
	{
		deleter_and_live_counter(game_process, &live_counter,
			&player_process, player_process_begin);
	}
	if (live_counter >= NBR_LIVE)
	{
		game_process->cycle_to_die -= CYCLE_DELTA;
		if (game_process->flag_v & 2)
			ft_printf("Cycle to die is now %d\n",
			(int32_t)game_process->cycle_to_die);
		game_process->checks_counter = 0;
	}
}

void	check_alives_1(t_game_process *game_process,
	int *cycles_counter_between_checks,
	t_player_process **player_process)
{
	game_process->checks_counter += 1;
	check_alives(game_process, player_process);
	*cycles_counter_between_checks = 0;
	if (game_process->checks_counter == MAX_CHECKS)
	{
		if (game_process->cycle_to_die > 0)
		{
			game_process->cycle_to_die -= CYCLE_DELTA;
			if (game_process->flag_v & 2)
				ft_printf("Cycle to die is now %d\n",
				(int32_t)game_process->cycle_to_die);
		}
		game_process->checks_counter = 0;
	}
}
