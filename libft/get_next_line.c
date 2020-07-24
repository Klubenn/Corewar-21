/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:30:07 by gtristan          #+#    #+#             */
/*   Updated: 2019/10/12 16:21:13 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	char	*a;
	char	*tmp;
	int		c;
	int		d;
	int		j;

	a = ft_strchr(*buf_list, '\n');
	c = ft_strlen(*buf_list);
	if (a)
	{
		d = ft_strlen(a);
		j = c - d;
		if (!(*line = ft_strndup(*buf_list, j)))
			return (-1);
		if (!(tmp = ft_strsub(*buf_list, j + 1, BUFF_SIZE)))
			return (-1);
		free(*buf_list);
		*buf_list = tmp;
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*buf_list[11000];
	char		buff[BUFF_SIZE + 1];
	int			e;
	int			f;

	if (read(fd, buff, 0) < 0)
		return (-1);
	if (buf_list[fd])
	{
		f = ft_prev_proc(&(buf_list[fd]), line);
		if (f != 0)
			return (f);
	}
	e = ft_read(fd, &(buf_list[fd]), line);
	if (e != 0)
		return (e);
	if (buf_list[fd] && buf_list[fd][0])
	{
		if (!(*line = ft_strdup(buf_list[fd])))
			return (-1);
		free(buf_list[fd]);
		buf_list[fd] = NULL;
		return (1);
	}
	return (0);
}
