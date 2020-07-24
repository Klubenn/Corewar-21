/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:32:17 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 23:10:22 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void	player_position_accordance_finder(t_game_process *game_process,
	t_player_list *player_list, int32_t arg, t_player_process *player_process)
{
	bool flag;

	flag = false;
	while (player_list)
	{
		if (arg == (-1 * player_list->position))
		{
			game_process->last_live_player = player_list;
			flag = true;
			break ;
		}
		player_list = player_list->next;
	}
	player_process->live_counter += 1;
	player_process->last_live_cycle_number = game_process->cycle_number;
	print_operation_logs(player_process, &arg, game_process);
	if ((game_process->flag_v & 1) && flag == true)
		ft_printf("Player %d (%s) is said to be alive\n",
			player_list->position,
				player_list->player->player_header.prog_name);
}

void	op1(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	int32_t arg;

	player_process->arg_position = (player_process->pc + 1) % MEM_SIZE;
	vm_field_memory->modulo = false;
	arg = (int32_t)take_value_from_field(vm_field_memory, player_process,
		(int)(game_process->op_tab[player_process->operation_code].dir_size),
			(u_int8_t)DIR_CODE);
	player_position_accordance_finder(game_process,
		game_process->player_list, arg, player_process);
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}
