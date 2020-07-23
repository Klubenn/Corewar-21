/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args_and_put_value.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:51:16 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 22:40:27 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		put_value_to_field(u_int32_t value,
	t_vm_field_memory *vm_field_memory, u_int64_t pc)
{
	int i;

	i = 0;
	while (i < 4)
	{
		vm_field_memory->field[(pc + i) % MEM_SIZE] =
			(u_int8_t)(value >> ((3 - i) * 8));
		i++;
	}
}

void		put_value_to_register(u_int8_t *regist, u_int32_t value)
{
	int i;

	i = 0;
	while (i < 4)
	{
		*regist = (u_int8_t)(value >> (8 * i));
		i++;
		regist++;
	}
}

u_int8_t	size_definer(t_player_process *player_process,
	t_vm_field_memory *vm_field_memory, int i)
{
	return ((player_process->args[i] == IND_CODE)
		? IND_SIZE : vm_field_memory->op_tab[player_process->
			operation_code].dir_size);
}

int32_t		process_args(int i, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int8_t	reg;
	int32_t		number;
	u_int8_t	size;

	size = size_definer(player_process, vm_field_memory, i);
	if (player_process->arg_position < 0)
		return (0);
	if (player_process->args[i] == REG_CODE)
	{
		reg = (u_int8_t)vm_field_memory->field[(player_process->
			arg_position) % MEM_SIZE];
		if (reg < 1 || reg > REG_NUMBER)
		{
			player_process->arg_position = -1;
			return (0);
		}
		number = *(int32_t *)(&(player_process->
			registers[reg * REG_SIZE - REG_SIZE]));
		player_process->reg[i] = reg;
		player_process->arg_position += 1;
	}
	else
		number = take_value_from_field(vm_field_memory,
			player_process, size, player_process->args[i]);
	return (number);
}
