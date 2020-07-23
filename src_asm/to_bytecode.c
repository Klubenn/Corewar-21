/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_bytecode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			write_to_array(char *ptr, char c)
{
	*ptr = c;
}

void			write_backwards(t_struct *data, void *source, int size)
{
	char *c;

	c = (char *)source;
	while (--size >= 0)
	{
		write_to_array(data->file_arr, *(c + size));
		(data->file_arr)++;
	}
}

void			bin_magic(t_struct *data)
{
	int x;

	x = COREWAR_EXEC_MAGIC;
	write_backwards(data, &x, sizeof(int));
}

void			bin_null(t_struct *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		write_to_array(data->file_arr, (char)0);
		(data->file_arr)++;
		i++;
	}
}

void			bin_exec_code_size(t_struct *data)
{
	int size;

	size = data->code_length;
	write_backwards(data, &size, sizeof(int));
}
