/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_field_memory_allocator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 17:58:25 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/22 17:59:19 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	memory_allocator_for_vm(t_player_list *player_list,
	int divider, unsigned char *field)
{
	int upper_boundary;
	int lower_boundary;
	int counter;

	counter = 0;
	upper_boundary = (MEM_SIZE / divider) * player_list->position;
	lower_boundary = (MEM_SIZE / divider) * (player_list->position - 1);
	while (lower_boundary < upper_boundary)
	{
		if ((u_int32_t)counter < player_list->player->player_header.prog_size)
			field[lower_boundary] = player_list->player->code[counter];
		else
			field[lower_boundary] = 0;
		counter++;
		lower_boundary++;
	}
}

int		vm_field_memory_initializer(t_vm_field_memory **vm_field_memory,
	t_op *op_tab)
{
	if (!(*vm_field_memory =
		(t_vm_field_memory *)ft_memalloc(sizeof(t_vm_field_memory))))
	{
		perror("Error");
		return (1);
	}
	if (!((*vm_field_memory)->field =
		(unsigned char *)ft_memalloc((size_t)MEM_SIZE * sizeof(u_int8_t))))
	{
		free(*vm_field_memory);
		perror("Error");
		return (1);
	}
	(*vm_field_memory)->op_tab = op_tab;
	return (0);
}
