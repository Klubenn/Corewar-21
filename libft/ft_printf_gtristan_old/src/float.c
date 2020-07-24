/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:36:48 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 17:50:44 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

unsigned long	power(int base, int exp)
{
	unsigned long num;

	num = 1;
	while (exp > 0)
	{
		num = num * base;
		exp--;
	}
	return (num);
}

t_dnum			*new_flist(unsigned long i, t_dnum *prevlist)
{
	t_dnum *flist;

	flist = (t_dnum *)malloc(sizeof(t_dnum));
	flist->num = i;
	flist->prev = prevlist;
	flist->next = NULL;
	return (flist);
}

void			change_flist(t_dnum *flist, unsigned long numpower)
{
	while (flist)
	{
		flist->num *= numpower;
		flist = flist->next;
	}
}

void			multiply(t_dnum *flist, unsigned long numpower)
{
	t_dnum			*flistcp;
	unsigned long	tmp;

	flistcp = flist;
	change_flist(flist, numpower);
	flist = flistcp;
	while (flist)
	{
		tmp = flist->num / 100000000;
		flist->num = flist->num % 100000000;
		if (flist->next)
		{
			flist = flist->next;
			flist->num += tmp;
		}
		else if (tmp)
		{
			flist->next = new_flist(tmp, flist);
			break ;
		}
		else
			flist = flist->next;
	}
}

void			floattostr2(t_dnum *flist, char *str, int len)
{
	char *tmp;

	while (flist->prev->prev)
	{
		flist = flist->prev;
		len = numlength(flist->num, 10);
		while (len++ < 8)
		{
			*str = '0';
			str++;
		}
		tmp = ft_itoa_base_u1(flist->num, 10, 0);
		str = ft_strcpy_pf(str, tmp);
		free(tmp);
	}
}
