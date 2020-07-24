/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:37:15 by couida            #+#    #+#             */
/*   Updated: 2020/07/24 15:56:44 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

int		change_num(char *str, int i)
{
	while (i >= 0)
	{
		if (str[i] < '9')
		{
			str[i] = str[i] + 1;
			break ;
		}
		str[i] = '0';
		i--;
	}
	return (i);
}

void	rounding3(t_list_pf *list, char *str, int i)
{
	char *tmp;
	char *tmp1;

	i = change_num(str, i - 1);
	if (i < 0)
		i = change_num(list->leftfl, ft_strlen_pf(list->leftfl) - 1);
	if (i < 0)
	{
		tmp = create_string('1', 1);
		tmp1 = list->leftfl;
		list->leftfl = ft_strjoin(tmp, tmp1);
		free(tmp);
		free(tmp1);
	}
}

char	*rounding2(t_list_pf *list, int i, int j)
{
	char *str;

	str = (char *)malloc(sizeof(char) * (i + 1));
	str = ft_strncpy(str, list->rightfl, i);
	str[i] = '\0';
	if (list->rightfl[i] > '5')
		rounding3(list, str, i);
	else if (list->rightfl[i] == '5')
	{
		if (list->rightfl[i - 1] % 2 == 0)
		{
			j = i;
			while (list->rightfl[++j])
				if (list->rightfl[j] > '0')
				{
					rounding3(list, str, i);
					break ;
				}
		}
		else
			rounding3(list, str, i);
	}
	return (str);
}

char	*rounding1(t_list_pf *list)
{
	int		i;
	int		j;
	char	*str;
	char	*tmp;

	j = ft_strlen_pf(list->rightfl);
	i = list->right;
	if (j <= i)
	{
		tmp = create_string('0', i - j);
		str = ft_strjoin(list->rightfl, tmp);
		free(tmp);
	}
	else
		return (rounding2(list, i, j));
	return (str);
}
