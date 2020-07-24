/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_value_from_field.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:46:28 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_vm/corewar.h"

int32_t		make_number_positive(int64_t number)
{
	while (number < 0)
		number += MEM_SIZE;
	return ((int32_t)(number % MEM_SIZE));
}

void		m_n(t_vm_field_memory *vm_field_memory,
t_player_process *player_process, int32_t number)
{
	if (vm_field_memory->modulo == false)
		player_process->arg_position = make_number_positive(((int64_t)number
			% (int64_t)IDX_MOD) + (int64_t)player_process->pc);
	else
		player_process->arg_position = make_number_positive((int64_t)number
			+ (int64_t)player_process->pc);
}

u_int32_t	bites_aggregator(t_vm_field_memory *vm_field_memory,
		t_player_process *player_process, int size, int32_t *i)
{
	u_int32_t tmp;

	tmp = 0;
	tmp = (u_int8_t)(vm_field_memory->
		field[player_process->arg_position % MEM_SIZE]);
	tmp = tmp << ((size - 1 - *i) * 8);
	(player_process->arg_position)++;
	*i += 1;
	return (tmp);
}

int32_t		take_value_from_field(t_vm_field_memory *vm_field_memory,
	t_player_process *player_process, int size, u_int8_t type)
{
	int32_t		number;
	int32_t		i;

	number = 0;
	i = 0;
	while (i < size)
		number = number |
			bites_aggregator(vm_field_memory,
			player_process, size, &i);
	if (i == 2)
		number = (int32_t)(int16_t)number;
	if (type == IND_CODE)
	{
		i = player_process->arg_position;
		m_n(vm_field_memory, player_process, number);
		number = take_value_from_field(vm_field_memory,
			player_process, DIR_SIZE, DIR_CODE);
		player_process->arg_position = i;
		return (number);
	}
	return (number);
}
