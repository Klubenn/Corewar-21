/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op4_op5_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 20:34:33 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 22:40:27 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	op4_op5_helper(int32_t *arg_value, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	if (player_process->arg_position >= 0)
		arg_value[2] = (u_int8_t)(vm_field_memory->
			field[(player_process->arg_position) % MEM_SIZE]);
	else
		arg_value[2] = 0;
	player_process->reg[2] = arg_value[2];
}
