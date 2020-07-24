/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_list_deleter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:49:09 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void			make_returner(t_player_list **returner,
	t_player_list *player_list, t_player_list *player_list_returner)
{
	*returner = player_list_returner;
	free(player_list);
}

void			stack_deleter_helper(t_player_list **player_list,
	t_player_list **returner)
{
	if ((*player_list)->next != 0 && (*player_list)->prev != 0)
	{
		(*player_list)->prev->next = (*player_list)->next;
		(*player_list)->next->prev = (*player_list)->prev;
		make_returner(returner, (*player_list), (*player_list)->prev);
	}
	else if ((*player_list)->next == 0 && (*player_list)->prev != 0)
	{
		(*player_list)->prev->next = NULL;
		make_returner(returner, (*player_list), (*player_list)->prev);
	}
	else if ((*player_list)->next != 0 && (*player_list)->prev == 0)
	{
		(*player_list)->next->prev = NULL;
		make_returner(returner, (*player_list), (*player_list)->next);
	}
	else if ((*player_list)->next == 0 && (*player_list)->prev == 0)
		free((*player_list));
}

t_player_list	*stack_deleter(t_player_list *player_list, int flag)
{
	t_player_list *returner;

	returner = NULL;
	stack_deleter_helper(&player_list, &returner);
	if (flag == 0)
		while (returner != NULL && returner->prev != NULL)
			returner = returner->prev;
	return (returner);
}
