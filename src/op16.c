/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op16.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:34:10 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 22:59:06 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	op16(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;

	regnum = vm_field_memory->field[(player_process->pc + 2) % MEM_SIZE];
	player_process->reg[0] = (int32_t)regnum;
	if (regnum > 0 &&
		regnum <= REG_NUMBER &&
			game_process->flag_a)
		ft_printf("Aff: %c\n",
			player_process->registers[regnum * REG_SIZE - REG_SIZE]);
	move_pc(game_process->op_tab,
		player_process, game_process, vm_field_memory);
}
