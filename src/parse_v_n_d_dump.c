/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_v_n_d_dump.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:30:09 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 22:40:27 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

bool	parse_dump(char **argv, int *count,
	t_game_process *game_process)
{
	if (*argv && ft_atoi(*argv) >= 0 &&
			check_atoi_honest(*argv) == 1 &&
				count[0] == 0 && count[1] == 0)
	{
		game_process->dump_cycle = ft_atoi(*argv);
		game_process->bytes_dump_per_line = 32;
		game_process->dump_flag = true;
		count[0]++;
		return (true);
	}
	else
	{
		game_process->error_flag = true;
		return (false);
	}
}

bool	parse_d(char **argv, int *count,
	t_game_process *game_process)
{
	if (*argv && ft_atoi(*argv) >= 0 &&
		check_atoi_honest(*argv) == 1 &&
			count[0] == 0 && count[1] == 0)
	{
		game_process->d_cycle = ft_atoi(*argv);
		game_process->bytes_dump_per_line = 64;
		game_process->dump_flag = true;
		count[1]++;
		return (true);
	}
	else
	{
		game_process->error_flag = true;
		return (false);
	}
}

bool	parse_n(char ***argv,
	t_player_list **player_list_2, t_game_process *game_process)
{
	if (**argv && ft_atoi(**argv) > 0 && ft_atoi(**argv) <= 4 &&
		check_atoi_honest(**argv) == 1 && *((*argv) + 1) &&
			ft_strcmp(*((*argv) + 1), "-n") != 0)
	{
		(*argv)++;
		if (put_in_stack_of_players(ft_atoi(*((*argv) - 1)),
			**argv, player_list_2))
		{
			game_process->error_flag = false;
			return (false);
		}
		return (true);
	}
	else
	{
		game_process->error_flag = true;
		return (false);
	}
}

bool	parse_v(t_player_list *player_list_1,
	t_player_list **player_list_2, t_game_process *game_process,
	char **begin_buff_argv)
{
	if (*(game_process->argv + 1) != 0 && game_process->count[2] == 0)
		game_process->flag_v = (uint8_t)(ft_atoi(*(game_process->argv + 1)));
	else
	{
		game_process->error_flag = true;
		error_manager_for_parse_arguments(player_list_1,
			*player_list_2, game_process, begin_buff_argv);
	}
	game_process->argv += 1;
	game_process->count[2]++;
	return (true);
}
