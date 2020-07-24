/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_completer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:39:30 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_vm/corewar.h"

void (*g_operation[17])(t_game_process *game_process,
	t_player_process *player_process,
	t_vm_field_memory *vm_field_memory) =
{
	0,
	op1,
	op2,
	op3,
	op4,
	op5,
	op6,
	op7,
	op8,
	op9,
	op10,
	op11,
	op12,
	op13,
	op14,
	op15,
	op16
};

void	operation_completer(t_game_process *game_process,
	t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	g_operation[game_process->
	op_tab[player_process->operation_code].bytecode_operation](game_process,
	player_process, vm_field_memory);
}
