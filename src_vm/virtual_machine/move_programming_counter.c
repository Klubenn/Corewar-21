/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_programming_counter.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:35:04 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_vm/corewar.h"

void	move_pc_logger(t_game_process *game_process,
	t_vm_field_memory *vm_field_memory,
	t_player_process *player_process, int *counter)
{
	if (ft_strcmp(game_process->op_tab[player_process->operation_code].name,
		"zjmp") == 0 && player_process->carry == true)
		return ;
	if (game_process->flag_v & 16)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ",
		counter[1], counter[2], (int)player_process->pc);
		while ((int)counter[2] % MEM_SIZE != (int)player_process->pc)
		{
			ft_printf("%02x ",
			vm_field_memory->field[(u_int64_t)counter[2] % MEM_SIZE]);
			counter[2] += 1;
		}
		ft_printf("\n");
	}
}

void	move_pc_helper_1(t_op *op_tab,
	t_player_process *player_process, int *counter)
{
	u_int8_t	op_code;

	op_code = player_process->operation_code;
	if (player_process->args[counter[0]] == REG_CODE)
	{
		player_process->pc = (player_process->pc + 1) % MEM_SIZE;
		counter[1] += 1;
	}
	else if (player_process->args[counter[0]] == IND_CODE)
	{
		player_process->pc = (player_process->pc + IND_SIZE) % MEM_SIZE;
		counter[1] += IND_SIZE;
	}
	else if (player_process->args[counter[0]] == DIR_CODE)
	{
		player_process->pc = (player_process->pc
		+ op_tab[op_code].dir_size) % MEM_SIZE;
		counter[1] += op_tab[op_code].dir_size;
	}
}

void	move_pc_helper(t_op *op_tab,
	t_player_process *player_process, int *counter)
{
	u_int8_t	op_code;

	op_code = player_process->operation_code;
	if (op_tab[op_code].arg_types[counter[0]] == REG_CODE)
	{
		player_process->pc = (player_process->pc + 1) % MEM_SIZE;
		counter[1] += 1;
	}
	else if (op_tab[op_code].arg_types[counter[0]] == IND_CODE)
	{
		player_process->pc = (player_process->pc + IND_SIZE) % MEM_SIZE;
		counter[1] += IND_SIZE;
	}
	else if (op_tab[op_code].arg_types[counter[0]] == DIR_CODE)
	{
		player_process->pc = (player_process->pc
		+ op_tab[op_code].dir_size) % MEM_SIZE;
		counter[1] += op_tab[op_code].dir_size;
	}
}

bool	move_pc(t_op *op_tab, t_player_process *player_process,
	t_game_process *game_process, t_vm_field_memory *vm_field_memory)
{
	int counter[3];

	counter[0] = 0;
	counter[1] = 0;
	counter[2] = (int)(player_process->pc);
	if (op_tab[player_process->operation_code].have_a_code_type_code == 0)
	{
		move_pc_helper(op_tab, player_process, counter);
		player_process->pc = (player_process->pc + 1) % MEM_SIZE;
		counter[1] += 1;
		move_pc_logger(game_process, vm_field_memory,
			player_process, counter);
		return (false);
	}
	while (counter[0] < op_tab[player_process->operation_code].args_number)
	{
		move_pc_helper_1(op_tab, player_process, counter);
		counter[0]++;
	}
	player_process->pc = (player_process->pc + 2) % MEM_SIZE;
	counter[1] += 2;
	move_pc_logger(game_process, vm_field_memory,
			player_process, counter);
	return (false);
}
