/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_stack_of_players.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:53:18 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/27 16:04:07 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

int	stack_member_initializer(t_player_list **player_list,
	int pos, t_player *player, t_player_list *player_list_prev)
{
	if (!((*player_list) = (t_player_list *)ft_memalloc(sizeof(t_player_list))))
		return (1);
	(*player_list)->player = player;
	(*player_list)->next = NULL;
	(*player_list)->prev = player_list_prev;
	if (pos > 0)
		(*player_list)->position = pos;
	else
		(*player_list)->position = 0;
	return (0);
}

int	put_in_stack_of_players_helper(t_player_list **player_list,
	t_player *player, int pos)
{
	t_player_list	*player_list_loc;

	player_list_loc = *player_list;
	if (player_list_loc == NULL)
		return (stack_member_initializer(player_list, pos, player, NULL));
	else
	{
		while (player_list_loc->next != 0)
		{
			if (pos == player_list_loc->position && pos != 0)
				break ;
			player_list_loc = player_list_loc->next;
		}
		if (pos == player_list_loc->position && pos != 0)
		{
			free(player->code);
			free(player);
			print_usage();
			return (1);
		}
		if (stack_member_initializer(&(player_list_loc->next),
			pos, player, player_list_loc))
			return (1);
		return (0);
	}
}

int	check_arguments_errors(int fd, char *player_name, t_player **player)
{
	if (fd < 0)
	{
		if (errno == 0)
			ft_printf("Can't read source file %s\n%z", player_name, 2);
		else
			perror("Error");
		return (1);
	}
	if (!((*player) = (t_player *)ft_memalloc(sizeof(t_player))))
	{
		perror("Error");
		return (1);
	}
	if (players_reader_parse_champions(fd, *player, &player_name))
	{
		free(*player);
		return (1);
	}
	return (0);
}

int	put_in_stack_of_players(int pos, char *player_name,
	t_player_list **player_list)
{
	t_player	*player;
	int			fd;

	fd = open(player_name, O_RDONLY);
	if (ft_strstr(player_name, ".cor") == NULL)
	{
		if (errno == 0)
			ft_printf("Wrong file format %s\n%z", player_name, 2);
		else
			perror("Error");
		return (1);
	}
	if (check_arguments_errors(fd, player_name,
		&player))
		return (1);
	close(fd);
	if (put_in_stack_of_players_helper(player_list, player, pos))
	{
		if (errno != 0)
			perror("Error");
		return (1);
	}
	return (0);
}
