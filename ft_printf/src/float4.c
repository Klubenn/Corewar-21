/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:37:28 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:37:32 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header_pf.h"

void	free_flist(t_dnum *flist)
{
	t_dnum *tmp;

	while (flist)
	{
		tmp = flist;
		flist = flist->prev;
		free(tmp);
	}
}

char	*floattostr1(t_dnum *flist)
{
	char	*str;
	char	*str0;
	char	*tmp;
	int		i;
	int		len;

	i = 1;
	if (!flist)
		return (NULL);
	while (flist->next)
	{
		flist = flist->next;
		i++;
	}
	len = numlength(flist->num, 10);
	str = (char *)malloc(sizeof(char) * ((i * 8) + len + 1));
	str0 = str;
	tmp = ft_itoa_base_u1(flist->num, 10, 0);
	ft_strcpy(str, tmp);
	free(tmp);
	str += len;
	floattostr2(flist, str, len);
	free_flist(flist);
	return (str0);
}

char	*conversion(unsigned long mant, int exp, int base)
{
	t_dnum	*flist;
	t_dnum	*flistcp;
	int		small;
	int		big;

	small = 25;
	if (base == 5)
		small = 10;
	big = power(base, small);
	flist = new_flist(0, NULL);
	flistcp = flist;
	while (mant > 0)
	{
		flist->next = new_flist((mant % 100000000), flist);
		mant /= 100000000;
		flist = flist->next;
	}
	flist = flistcp;
	while (exp >= small)
	{
		multiply(flist->next, big);
		exp -= small;
	}
	multiply(flist->next, power(base, exp));
	return (floattostr1(flist->next));
}

void	print_in(t_list_pf *list)
{
	int a;

	a = list->left - ft_strlen_pf(list->number);
	list->print[1] = list->number;
	list->number = NULL;
	if (a > 0)
	{
		if (list->flag0[1])
			list->print[2] = create_string(' ', a);
		else
			list->print[0] = create_string(' ', a);
	}
	printnum(list);
}

int		inf_nan(int sign, unsigned long mant, int exp, t_list_pf *list)
{
	if (mant == 13835058055282163712lu && exp == 32767)
	{
		list->number = ft_makestr("nan");
		print_in(list);
		return (1);
	}
	else if (mant == 9223372036854775808lu && exp == 32767)
	{
		if (sign)
			list->number = ft_makestr("-inf");
		else
			list->number = ft_makestr("inf");
		print_in(list);
		return (1);
	}
	return (0);
}
