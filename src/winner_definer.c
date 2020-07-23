/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner_definer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:50:32 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 22:40:27 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	winner_definer(t_player_list *player_list, t_game_process *game_process)
{
	if (game_process->last_live_player)
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
			game_process->last_live_player->position,
				game_process->last_live_player->
				player->player_header.prog_name);
		return ;
	}
	while (player_list->next)
		player_list = player_list->next;
	ft_printf("Contestant %d, \"%s\", has won !\n", player_list->position,
		player_list->player->player_header.prog_name);
}
