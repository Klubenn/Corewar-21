/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skips.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*trim_start(char *str)
{
	if (str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
	}
	return (str);
}

int		skip_spaces(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int		skip_word(char *str)
{
	int i;

	i = 0;
	while (!ft_isspace(str[i]) && str[i] != '\0')
		i++;
	return (i);
}

int		check_ending(char *str)
{
	if (str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (!*str || *str == COMMENT_CHAR)
			return (0);
	}
	return (1);
}

char	*cut_string(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	while (str[i] && str[i] != COMMENT_CHAR)
		i++;
	if (!(new = ft_strndup(str, i)))
		return (NULL);
	return (new);
}
