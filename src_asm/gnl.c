/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_buf_to_line(char *buff, size_t i, char **line, char **buf_list)
{
	char *tmp;

	if (!(tmp = ft_strndup(buff, i)))
		return (-1);
	if (!(*buf_list))
		if (!(*buf_list = ft_strnew(0)))
			return (-1);
	if (!(*line = ft_strjoin(*buf_list, tmp)))
		return (-1);
	free(*buf_list);
	free(tmp);
	if (!(*buf_list = ft_strsub(buff, i + 1, BUFF_SIZE)))
		return (-1);
	return (1);
}

static int	ft_read(const int fd, char **buf_list, char **line)
{
	char	*tmp;
	char	buff[BUFF_SIZE + 1];
	int		ret;
	size_t	i;

	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		i = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
				return (ft_buf_to_line(buff, i, line, buf_list));
			i++;
		}
		if (*buf_list)
			tmp = *buf_list;
		else
			tmp = ft_strnew(0);
		if (!(*buf_list = ft_strjoin(tmp, buff)))
			return (-1);
		free(tmp);
	}
	return (ret);
}

static int	ft_prev_proc(char **buf_list, char **line)
{
	char	*rest;
	char	*tmp;
	int		len;

	rest = ft_strchr(*buf_list, '\n');
	if (rest)
	{
		len = rest - *buf_list;
		if (!(*line = ft_strndup(*buf_list, len)))
			return (-1);
		if (!(tmp = ft_strsub(*buf_list, len + 1, BUFF_SIZE)))
			return (-1);
		free(*buf_list);
		*buf_list = tmp;
		return (1);
	}
	return (0);
}

int			gnl(const int fd, char **line, char **gnl_buf)
{
	char		buff[BUFF_SIZE + 1];
	int			e;
	int			f;

	if (read(fd, buff, 0) < 0)
		return (-1);
	if (*gnl_buf)
	{
		f = ft_prev_proc(gnl_buf, line);
		if (f != 0)
			return (f);
	}
	e = ft_read(fd, gnl_buf, line);
	if (e != 0)
		return (e);
	if (*gnl_buf)
	{
		if (!(*line = ft_strdup(*gnl_buf)))
			return (-1);
		free(*gnl_buf);
		*gnl_buf = NULL;
		return (1);
	}
	return (0);
}
