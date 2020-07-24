/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:37:49 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_args_endian_2(t_player_process *player_process,
	int32_t *arg_value, t_game_process *game_process)
{
	if (ft_strcmp(game_process->op_tab[player_process->
		operation_code].name, "ldi") == 0)
	{
		ft_printf("\n       | -> load from %d + %d = %d (with pc and mod %d)",
			arg_value[0], arg_value[1], arg_value[0] + arg_value[1],
				(int32_t)((int64_t)player_process->pc +
			(((int64_t)arg_value[0] + (int64_t)arg_value[1])
				% (int64_t)IDX_MOD)));
	}
	if (ft_strcmp(game_process->op_tab[player_process->
		operation_code].name, "lldi") == 0)
	{
		ft_printf("\n       | -> load from %d + %d = %d (with pc %d)",
			arg_value[0], arg_value[1], arg_value[0] + arg_value[1],
				(int32_t)((int64_t)player_process->pc +
				(int64_t)arg_value[0] + (int64_t)arg_value[1]));
	}
	ft_printf("\n");
}

void	print_args_endian_1(t_player_process *player_process,
	int32_t *arg_value, t_game_process *game_process)
{
	if (ft_strcmp(game_process->op_tab[player_process->
		operation_code].name, "fork") == 0 ||
		ft_strcmp(game_process->op_tab[player_process->
			operation_code].name, "lfork") == 0)
		ft_printf(" (%llu)", player_process->pc);
	if (ft_strcmp(game_process->op_tab[player_process->
		operation_code].name, "zjmp") == 0)
	{
		if (player_process->carry == true)
			ft_printf(" OK");
		else
			ft_printf(" FAILED");
	}
	if (ft_strcmp(game_process->op_tab[player_process->
		operation_code].name, "sti") == 0)
	{
		ft_printf("\n       | -> store to %d + %d = %d (with pc and mod %d)",
			arg_value[1], arg_value[2], arg_value[1] + arg_value[2],
				(int32_t)((int64_t)player_process->pc +
				(int64_t)(((int64_t)arg_value[1] + (int64_t)arg_value[2])
					% (int64_t)IDX_MOD)));
	}
	print_args_endian_2(player_process,
		arg_value, game_process);
}

void	print_args(t_player_process *player_process,
	int32_t *arg_value, t_game_process *game_process)
{
	int i;

	i = 0;
	if (game_process->op_tab[player_process->
		operation_code].have_a_code_type_code != 0)
	{
		while (i < game_process->op_tab[player_process->
			operation_code].args_number)
		{
			if (player_process->args[i] == 1 &&
				(game_process->op_tab[player_process->
					operation_code].arg_types[i]
					| T_REG) == T_REG)
				ft_printf(" r%d", (int32_t)player_process->reg[i]);
			else
				ft_printf(" %d", (int32_t)arg_value[i]);
			i++;
		}
	}
	else
		ft_printf(" %d", *arg_value);
	print_args_endian_1(player_process, arg_value, game_process);
}

void	print_operation_logs(t_player_process *player_process,
	int32_t *arg_value, t_game_process *game_process)
{
	if ((game_process->flag_v) & 4)
	{
		if (ft_strcmp(game_process->op_tab[player_process->
			operation_code].name, "fork") == 0 ||
			ft_strcmp(game_process->op_tab[player_process->
			operation_code].name, "lfork") == 0)
			ft_printf("P %4.llu | %s",
				player_process->parent,
					game_process->op_tab[player_process->operation_code].name);
		else
			ft_printf("P %4.llu | %s",
				player_process->ident, game_process->
				op_tab[player_process->operation_code].name);
		print_args(player_process, arg_value, game_process);
	}
}
