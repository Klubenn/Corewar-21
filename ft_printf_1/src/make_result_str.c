/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_result_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 16:39:11 by couida            #+#    #+#             */
/*   Updated: 2020/07/24 15:56:44 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_pf.h"

int		set_fd(int fd)
{
	static int loc_fd = 1;

	if (fd == -2)
		return (loc_fd);
	if (fd > 0)
		loc_fd = fd;
	return (0);
}

int		get_fd(void)
{
	return (set_fd(-2));
}

char	*add_new_part_to_res_str(char *str, int len, int how_much)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc(sizeof(char) * (size_t)(len + how_much));
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	return (res);
}

char	*add_char_to_output_buffer(char c)
{
	static int		len = 0;
	static char		*res_str = 0;
	int				size_part;

	size_part = 1000;
	if (c)
	{
		if (!(len % size_part))
			res_str = add_new_part_to_res_str(res_str, len, size_part);
		res_str[len] = c;
		len++;
		res_str[len] = '\0';
	}
	return (res_str);
}
