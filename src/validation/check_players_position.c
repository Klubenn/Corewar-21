/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_players_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:33:03 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	check_position_help(t_player_list *player_list_2, int len)
{
	if (len > MAX_PLAYERS)
	{
		if (errno == 0)
			fprintf(stderr, "Too many champions\n");
		else
			perror("Error");
		return (1);
	}
	while (player_list_2 != 0)
	{
		if (player_list_2->position > len)
		{
			print_usage();
			return (1);
		}
		player_list_2 = player_list_2->next;
	}
	if (len == 0)
	{
		print_usage();
		return (1);
	}
	return (0);
}

int	check_position(t_player_list *player_list_1, t_player_list *player_list_2)
{
	int len;

	len = 0;
	while (player_list_1 != 0)
	{
		len++;
		player_list_1 = player_list_1->next;
	}
	player_list_1 = player_list_2;
	while (player_list_1 != 0)
	{
		len++;
		player_list_1 = player_list_1->next;
	}
	if (check_position_help(player_list_2, len))
		return (1);
	return (0);
}
