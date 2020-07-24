/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:15:39 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/15 11:30:42 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_math(int x, int y, int *res, char oper)
{
	int a;

	a = 0;
	if ((oper == '%' || oper == '/') && y == 0)
	{
		ft_putstr("Wrong argument: can'd divide by zero\n");
		return (0);
	}
	else if (oper == '+')
		a = (x + y);
	else if (oper == '-')
		a = (x - y);
	else if (oper == '*')
		a = (x * y);
	else if (oper == '/')
		a = (x / y);
	else if (oper == '%')
		a = (x % y);
	*res = a;
	return (1);
}
