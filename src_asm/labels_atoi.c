/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	find_label(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			return (i);
		if (!ft_strchr(LABEL_CHARS, str[i]))
			return (0);
		i++;
	}
	return (0);
}

int			check_label(t_struct *data, char *str)
{
	int		len;
	t_label	*lab;

	if ((len = find_label(str)))
	{
		data->label_present = 1;
		if (!data->label)
		{
			if (!(data->label = (t_label *)ft_memalloc(sizeof(t_label))))
				return (-1);
			data->label->label_name = ft_strndup(str, len);
			return (len + 1);
		}
		lab = data->label;
		while (lab->next)
			lab = lab->next;
		if (!(lab->next = (t_label *)ft_memalloc(sizeof(t_label))))
			return (-1);
		lab->next->label_name = ft_strndup(str, len);
		return (len + 1);
	}
	return (0);
}

static int	check_atoi_conditions(char arg, int digits, int size,
									long long result)
{
	if (arg || digits > 10 || (size == 2 && (result > SHRT_MAX ||
	result < SHRT_MIN)) || (size == 4 && (result > INT_MAX ||
	result < INT_MIN)) || (size == 1 && (result < 1 || result > REG_NUMBER)))
		return (1);
	return (0);
}

int			corewar_atoi(char *arg, void *numptr, int size, int digits)
{
	long long	result;
	int			sign;
	int			*num;

	sign = 1;
	result = 0;
	if (!arg || !*arg)
		return (1);
	if (*arg == '-' && arg++)
		sign = -1;
	while (*arg >= '0' && *arg <= '9' && digits <= 10)
	{
		result = result * 10 + (*arg - '0');
		digits = result == 0 ? 1 : digits + 1;
		arg++;
	}
	result *= sign;
	if (check_atoi_conditions(*arg, digits, size, result))
		return (1);
	num = numptr;
	*num = size == 1 ? (char)result : *num;
	*num = size == 2 ? (short)result : *num;
	*num = size == 4 ? (int)result : *num;
	return (0);
}
