/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:37:39 by couida            #+#    #+#             */
/*   Updated: 2020/07/24 15:56:44 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_struct(t_list_pf *list)
{
	int i;

	i = 0;
	if (list)
	{
		ft_free(&list->number);
		ft_free(&list->leftfl);
		ft_free(&list->rightfl);
		ft_free(&list->zero);
		while (i <= 7)
		{
			ft_free(&list->print[i]);
			i++;
		}
		free(list);
	}
}
