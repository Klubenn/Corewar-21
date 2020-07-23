/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_stack_creator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:37:52 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 22:40:27 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			player_stack_creator_helper_2(t_player_list **player_list_final,
	t_player_list *player_list_buff, t_player_list **player_list,
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
	(*player_list_final)->player = player_list_buff->player;
	(*player_list_final)->position = player_list_buff->position;
	(*player_list_final)->next = NULL;
	player_list[1] = stack_deleter(player_list_buff, 0);
}

void			player_stack_creator_helper_1(t_player_list **player_list_final,
	t_player_list *player_list_buff, t_player_list **player_list,
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
	(*player_list_final)->player = player_list_buff->player;
	(*player_list_final)->position = player_list_buff->position;
	(*player_list_final)->next = NULL;
	(*player_list_final)->prev = NULL;
	game_process->begin_list = *player_list_final;
	player_list[1] = stack_deleter(player_list_buff, 0);
}

void			player_stack_creator_2(t_player_list **player_list_final,
	int count, t_player_list **pl_list_mass,
	t_game_process *game_process)
{
	if (*player_list_final == NULL)
		player_stack_creator_helper_3(player_list_final, count,
			pl_list_mass, game_process);
	else
		player_stack_creator_helper_4(player_list_final, count,
			pl_list_mass, game_process);
}

void			player_stack_creator_1(t_player_list **player_list_final,
	t_player_list *player_list_buff, t_player_list **pl_list_mass,
	t_game_process *game_process)
{
	if (*player_list_final == NULL)
		player_stack_creator_helper_1(player_list_final, player_list_buff,
			pl_list_mass, game_process);
	else
		player_stack_creator_helper_2(player_list_final, player_list_buff,
			pl_list_mass, game_process);
}

t_player_list	*player_stack_creator(t_player_list *player_list_1,
	t_player_list *player_list_2, t_game_process *game_process)
{
	t_player_list	*player_list_final;
	t_player_list	*player_list_buff;
	t_player_list	*pl_list_mass[2];
	int				count;

	count = 1;
	player_list_final = NULL;
	player_list_buff = player_list_2;
	pl_list_mass[0] = player_list_1;
	pl_list_mass[1] = player_list_2;
	while (pl_list_mass[0] != NULL || pl_list_mass[1] != NULL)
	{
		player_list_buff = pl_list_mass[1];
		while (player_list_buff && player_list_buff->position != count)
			player_list_buff = player_list_buff->next;
		if (player_list_buff != NULL)
			player_stack_creator_1(&player_list_final, player_list_buff,
				pl_list_mass, game_process);
		else
			player_stack_creator_2(&player_list_final, count,
				pl_list_mass, game_process);
		count++;
	}
	return (game_process->begin_list);
}
