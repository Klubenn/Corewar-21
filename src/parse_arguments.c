/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:53:54 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 22:40:27 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			error_manager_for_parse_arguments(t_player_list *player_list_1,
	t_player_list *player_list_2, t_game_process *game_process,
		char **begin_buff_argv)
{
	bool error_flag;

	error_flag = game_process->error_flag;
	memory_deleter(player_list_2, 0, game_process);
	memory_deleter(player_list_1, 0, 0);
	arguments_memory_deleter(begin_buff_argv);
	if (error_flag == true)
		print_usage();
	exit(1);
}

bool			parse_arguments_2(t_game_process *game_process,
	t_player_list *player_list_1, t_player_list **player_list_2,
	char **begin_buff_argv)
{
	if (ft_strcmp(*(game_process->argv), "-n") == 0)
	{
		game_process->argv += 1;
		if (!(parse_n(&(game_process->argv),
			player_list_2, game_process)))
			error_manager_for_parse_arguments(player_list_1,
			*player_list_2, game_process, begin_buff_argv);
		return (true);
	}
	else if (ft_strcmp(*(game_process->argv),
		"-a") == 0)
	{
		game_process->flag_a = true;
		return (true);
	}
	else if (ft_strcmp(*(game_process->argv),
		"-v") == 0)
	{
		return (parse_v(player_list_1, player_list_2,
			game_process, begin_buff_argv));
	}
	else
		return (false);
}

bool			parse_arguments_1(t_player_list *player_list_1,
	t_player_list **player_list_2, t_game_process *game_process,
	char **begin_buff_argv)
{
	if (ft_strcmp(*(game_process->argv),
		"-dump") == 0)
	{
		game_process->argv += 1;
		if (!(parse_dump(game_process->argv,
			game_process->count, game_process)))
			error_manager_for_parse_arguments(player_list_1,
			*player_list_2, game_process, begin_buff_argv);
		return (true);
	}
	else if (ft_strcmp(*(game_process->argv), "-d") == 0)
	{
		game_process->argv += 1;
		if (!(parse_d(game_process->argv, game_process->count,
			game_process)))
			error_manager_for_parse_arguments(player_list_1,
			*player_list_2, game_process, begin_buff_argv);
		return (true);
	}
	else
		return (parse_arguments_2(game_process, player_list_1,
				player_list_2, begin_buff_argv));
}

t_player_list	*player_stack_creator_checker(t_player_list *player_list_1,
	t_player_list *player_list_2, char **begin_buff_argv,
	t_game_process *game_process)
{
	arguments_memory_deleter(begin_buff_argv);
	if (check_position(player_list_1, player_list_2))
	{
		memory_deleter(player_list_1, 0, 0);
		memory_deleter(player_list_2, 0, game_process);
		exit(1);
	}
	return (player_stack_creator(player_list_1, player_list_2,
		game_process));
}

void			parse_arguments(t_game_process *game_process,
	t_player_list **player_list)
{
	char			**begin_buff_argv;
	t_player_list	*player_list_1;
	t_player_list	*player_list_2;

	begin_buff_argv = game_process->argv;
	player_list_1 = NULL;
	player_list_2 = NULL;
	while (*(game_process->argv) != 0)
	{
		if (!(parse_arguments_1(player_list_1, &player_list_2,
			game_process, begin_buff_argv)))
		{
			if (put_in_stack_of_players(0,
				*(game_process->argv), &player_list_1))
			{
				game_process->error_flag = false;
				error_manager_for_parse_arguments(player_list_1,
					player_list_2, game_process, begin_buff_argv);
			}
		}
		(game_process->argv)++;
	}
	*player_list = player_stack_creator_checker(player_list_1, player_list_2,
		begin_buff_argv, game_process);
}
