/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:38:28 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:38:30 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header_pf.h"

int		parsing2(t_list_pf *list, va_list ap, char *ch)
{
	int	i;
	int ii;
	int a;

	ii = 0;
	while (*ch && (a = last_letter(*ch)) <= 0)
	{
		if (a == -1)
			i = 1;
		else if (*ch == '*')
		{
			if (!list->left)
				list->left = va_arg(ap, int);
			else
				list->right = va_arg(ap, int);
			i = 1;
		}
		else
			i = fill_struct1(ch, list);
		ii += i;
		ch += i;
	}
	return (ii);
}

int		parsing1(char *ch, va_list ap)
{
	int			ii;
	t_list_pf	*list;

	list = new_list();
	ii = parsing2(list, ap, ch);
	ch += ii;
	if (!*ch)
	{
		free_struct(list);
		return (ii);
	}
	ii++;
	list->letter = *ch;
	if (!list->flag0[0])
		list->flag0[0] = ' ';
	analysis(list, ap);
	free_struct(list);
	return (ii);
}
