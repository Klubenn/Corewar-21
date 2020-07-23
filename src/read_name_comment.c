/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_name_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	finish_reading(char **string, char *tmp2, char *small, char *big)
{
	char *tmp1;

	if (big)
		tmp1 = big;
	else
		tmp1 = ft_strdup("\n");
	if (!check_ending(tmp2 + 1))
	{
		big = ft_strndup(small, tmp2 - small);
		*string = ft_strjoin(tmp1, big);
		free_strings(small, tmp1, big, NULL);
		return (0);
	}
	free_strings(small, tmp1, NULL, NULL);
	return (SYNTAX_ERROR);
}

static int	continue_reading(int fd, char **string, t_struct *data)
{
	char	*small;
	char	*big;
	char	*tmp1;
	char	*tmp2;
	int		flag;

	flag = 0;
	tmp1 = ft_strdup("\n");
	big = NULL;
	while (gnl(fd, &small, &data->gnl_buf) > 0 && ++(data->line))
	{
		if ((tmp2 = ft_strchr(small, '"')))
		{
			if (!flag)
				free(tmp1);
			return (finish_reading(string, tmp2, small, big));
		}
		tmp2 = ft_strjoin(tmp1, small);
		big = ft_strjoin(tmp2, "\n");
		free_strings(tmp1, tmp2, small, NULL);
		tmp1 = big;
		flag = 1;
	}
	free(tmp1);
	return (QUOTES_END);
}

static int	write_name_comment(char *substring, t_struct *data, size_t len)
{
	if (len == PROG_NAME_LENGTH)
	{
		data->name = substring;
		if (ft_strlen(substring) > len)
			return (LONG_NAME);
	}
	else
	{
		data->comment = substring;
		if (ft_strlen(substring) > len)
			return (LONG_COMM);
	}
	return (0);
}

static int	extract_name_comment(char *str, t_struct *data, int fd, int len)
{
	char	*substring;
	char	*add_string;
	int		i;

	str = trim_start(str);
	if (!*str || *str != '"')
		return (QUOTES_BEGIN);
	i = 1;
	while (str[i] && str[i] != '"')
		i++;
	if (!str[i])
	{
		if ((i = continue_reading(fd, &add_string, data)))
			return (i);
		substring = ft_strjoin(str + 1, add_string);
		free(add_string);
	}
	else if (!check_ending(str + i + 1))
		substring = ft_strndup(str + 1, i - 1);
	else
		return (SYNTAX_ERROR);
	return (write_name_comment(substring, data, len));
}

void		process_name_and_comment(char *str, t_struct *data, int fd)
{
	int err;

	str = trim_start(str);
	if (*str == COMMENT_CHAR || !*str)
		return ;
	if (ft_strnequ(str, NAME_CMD_STRING, 5))
		err = (data->name ? MULTIPLE_NAME :
			extract_name_comment(str + 5, data, fd, PROG_NAME_LENGTH));
	else if (ft_strnequ(str, COMMENT_CMD_STRING, 8))
		err = (data->comment ? MULTIPLE_COMMENT :
			extract_name_comment(str + 8, data, fd, COMMENT_LENGTH));
	else
		err = (TOP_FILE);
	if (err)
		error_management(err, data, 0);
}
