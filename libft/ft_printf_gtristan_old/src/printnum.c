/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:38:57 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:38:59 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

void	printnum(t_list_pf *list)
{
	int i;

	i = 0;
	while (i <= 7)
	{
		ft_putstr_pf(list->print[i]);
		i++;
	}
}

int		sumlen(t_list_pf *list)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (i <= 5)
	{
		len = len + ft_strlen_pf(list->print[i]);
		i++;
	}
	return (len);
}

void	printnum_d2(t_list_pf *list, int a)
{
	if (list->flag0[1])
	{
		list->print[0] = create_string(list->flag0[2], 1);
		list->print[1] = list->number;
		list->print[2] = create_string(' ', list->left - sumlen(list));
	}
	else if (!list->flag0[2])
	{
		list->print[0] = create_string(list->flag0[0], list->left - a);
		list->print[1] = list->number;
	}
	else
	{
		list->print[1] = create_string(list->flag0[2], 1);
		list->print[3] = list->number;
		if (list->flag0[0] == ' ')
			list->print[0] = create_string(' ', list->left - sumlen(list));
		else if (list->flag0[0] == '0')
			list->print[2] = create_string('0', list->left - sumlen(list));
	}
	list->number = NULL;
}

void	printnum_d1(t_list_pf *list)
{
	int a;

	a = ft_strlen(list->number);
	if (list->point)
	{
		list->print[3] = create_string('0', list->right - a);
		list->print[4] = list->number;
		list->number = NULL;
		list->print[2] = create_string(list->flag0[2], 1);
		if (list->flag0[1])
			list->print[5] = create_string(' ', list->left - sumlen(list));
		else
			list->print[1] = create_string(' ', list->left - sumlen(list));
	}
	else
		printnum_d2(list, a);
	printnum(list);
}
