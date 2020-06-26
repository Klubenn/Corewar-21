/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: couida <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:38:40 by couida            #+#    #+#             */
/*   Updated: 2020/01/17 16:38:45 by couida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header_pf.h"

int		is_color(char *str, char *color)
{
	while (*str && *color)
		if (*(str++) != *(color++))
			return (0);
	return (1);
}

int		print_color(char *str)
{
	int			color_number;
	int			i;
	static char colors[][10] = {"{eoc}", "{red}", "{green}", "{yellow}",
								"{blue}", "{magenta}", "{cyan}"};

	i = -1;
	color_number = -1;
	while (++i < 7 && color_number == -1)
		color_number = is_color(str, colors[i]) > 0 ? i : -1;
	if (color_number == 0)
		ft_putstr_pf(RESET);
	else if (color_number == 1)
		ft_putstr_pf(RED);
	else if (color_number == 2)
		ft_putstr_pf(GREEN);
	else if (color_number == 3)
		ft_putstr_pf(YELLOW);
	else if (color_number == 4)
		ft_putstr_pf(BLUE);
	else if (color_number == 5)
		ft_putstr_pf(MAGENTA);
	else if (color_number == 6)
		ft_putstr_pf(CYAN);
	i = ft_strlen(colors[color_number]);
	return (i);
}
