/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op10.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 20:49:42 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	op10_player_process(int32_t *arg_value,
	t_player_process *player_process,
	t_vm_field_memory *vm_field_memory, u_int8_t *regnum)
{
	if (player_process->args[0] == DIR_CODE)
		arg_value[0] = (int32_t)((int16_t)process_args(0,
			player_process, vm_field_memory));
	else
		arg_value[0] = process_args(0, player_process,
			vm_field_memory);
	if (player_process->args[1] == DIR_CODE)
		arg_value[1] = (int32_t)((int16_t)process_args(1,
			player_process, vm_field_memory));
	else
		arg_value[1] = process_args(1,
			player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
		*regnum = vm_field_memory->
			field[player_process->arg_position];
	else
		*regnum = 0;
}

void	op10(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int8_t	regnum;
	int32_t		arg_value[2];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc
		+ 2) % MEM_SIZE;
	op10_player_process(arg_value, player_process,
		vm_field_memory, &regnum);
	player_process->reg[2] = regnum;
	if (regnum > 0 && regnum <= REG_NUMBER
		&& player_process->arg_position >= 0)
	{
		player_process->arg_position =
			make_number_positive((int64_t)player_process->pc +
			(((int64_t)arg_value[0] +
				(int64_t)arg_value[1]) % (int64_t)IDX_MOD));
		put_value_to_register(&player_process->registers[regnum *
			REG_SIZE - REG_SIZE],
				take_value_from_field(vm_field_memory,
					player_process, REG_SIZE, DIR_CODE));
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}
