/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:36:22 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:36:25 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header_pf.h"

int		fill_struct3(char *ch, t_list_pf *list)
{
	if (*ch == 'h')
	{
		if (*(ch + 1) == 'h')
		{
			list->flag1 = 2;
			return (2);
		}
		list->flag1 = 1;
	}
	else if (*ch == 'l')
	{
		if (*(ch + 1) == 'l')
		{
			list->flag1 = 4;
			return (2);
		}
		list->flag1 = 3;
	}
	return (1);
}

void	fill_struct2(char *ch, t_list_pf *list)
{
	if (*ch == '-')
		list->flag0[1] = '-';
	else if (*ch == '+' || *ch == ' ')
	{
		if (list->flag0[2] != '+')
			list->flag0[2] = *ch;
	}
	else if (*ch == '#')
		list->flag0[3] = *ch;
	else if (*ch == '.')
		list->point = *ch;
	else if (*ch == 'L')
		list->flag1 = 5;
	else if (*ch == '$')
		list->flag0[4] = *ch;
	else if (*ch == 39)
		list->flag0[5] = *ch;
}

int		fill_struct1(char *ch, t_list_pf *list)
{
	if (*ch >= '0' && *ch <= '9')
	{
		if (*ch == '0' && !list->left && !list->right)
			list->flag0[0] = '0';
		else if (list->point != '.')
		{
			list->left = ft_atoi(ch);
			return (numlength(list->left, 10));
		}
		else
		{
			list->right = ft_atoi(ch);
			return (numlength(list->right, 10));
		}
	}
	else if (*ch == 'h' || *ch == 'l')
		return (fill_struct3(ch, list));
	else
		fill_struct2(ch, list);
	return (1);
}

char	*create_string(char c, int i)
{
	char *s;

	if (i <= 0 || c == 0)
		i = 0;
	s = (char *)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	while (--i >= 0)
		s[i] = c;
	return (s);
}
