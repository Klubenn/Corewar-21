/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_stack_creator_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:45:09 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 22:29:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void	memory_is_not_enough(t_player_list *player_list_1,
	t_player_list *player_list_2, t_game_process *game_process)
{
	memory_deleter(player_list_1, 0, 0);
	memory_deleter(player_list_2, 0, 0);
	memory_deleter(game_process->begin_list, 0, game_process);
	perror("Error");
	exit(1);
}

void	player_stack_creator_helper_4(t_player_list **player_list_final,
	int count, t_player_list **player_list,
	t_game_process *game_process)
{
	if (!((*player_list_final)->next =
		(t_player_list *)ft_memalloc(sizeof(t_player_list))))
	{
		memory_deleter(player_list[0], 0, 0);
		memory_deleter(player_list[1], 0, 0);
		memory_deleter(game_process->begin_list, 0, game_process);
		perror("Error");
		exit(1);
	}
	(*player_list_final)->next->prev = (*player_list_final);
	(*player_list_final) = (*player_list_final)->next;
	(*player_list_final)->player = player_list[0]->player;
	(*player_list_final)->position = count;
	(*player_list_final)->next = NULL;
	player_list[0] = stack_deleter(player_list[0], 1);
}

void	player_stack_creator_helper_3(t_player_list **player_list_final,
	int count, t_player_list **player_list,
	t_game_process *game_process)
{
	if (!((*player_list_final) =
		(t_player_list *)ft_memalloc(sizeof(t_player_list))))
	{
		memory_deleter(player_list[0], 0, 0);
		memory_deleter(player_list[1], 0, 0);
		memory_deleter(game_process->begin_list, 0, game_process);
		perror("Error");
		exit(1);
	}
	(*player_list_final)->player = player_list[0]->player;
	(*player_list_final)->position = count;
	(*player_list_final)->next = NULL;
	(*player_list_final)->prev = NULL;
	game_process->begin_list = (*player_list_final);
	player_list[0] = stack_deleter(player_list[0], 1);
}
