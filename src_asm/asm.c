/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		to_bytecode(t_struct *data)
{
	int fd;

	data->file_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH +
				data->code_length;
	if (!(data->file_arr = (char *)ft_memalloc(sizeof(char) * data->file_size)))
		error_management(MALLOC_FAIL, data, -1);
	data->file_arr_start = data->file_arr;
	bin_magic(data);
	bin_champ_name(data);
	bin_null(data);
	bin_exec_code_size(data);
	bin_comment(data);
	bin_null(data);
	bin_exec_champ(data);
	fd = open(data->file_name, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		error_management(CANT_CREATE_FILE, data, -1);
	write(fd, data->file_arr_start, data->file_size);
	close(fd);
}

void		is_valid_file(char *file_name, t_struct *data)
{
	int			fd;
	int			flag;
	char		*str;
	int			ret;

	flag = 1;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		error_management(NO_FILE, data, -1);
	while ((ret = gnl(fd, &str, &data->gnl_buf)) > 0 && ++(data->line))
	{
		if (!data->name || !data->comment)
			process_name_and_comment(str, data, fd);
		else
			process_string(str, data, fd);
		flag = check_ending(str);
		free(str);
	}
	close(fd);
	if (ret == -1)
		error_management(NO_READ, data, -1);
	if (flag)
		error_management(END_INPUT, data, 0);
	data->line = 0;
}

t_struct	*change_extension(char *file_name)
{
	int			i;
	t_struct	*data;

	if (!file_name)
		error_management(NO_FILE, NULL, -1);
	i = ft_strlen(file_name) + 1;
	while (--i >= 0)
	{
		if (file_name[i] == '.')
		{
			if (i == 0 || ft_strcmp(file_name + i, ".s"))
				error_management(FILE_NAME, NULL, -1);
			else
			{
				if (!(data = (t_struct *)ft_memalloc(sizeof(t_struct))) ||
					!(data->file_name = (char *)ft_memalloc((i + 5) *
															(sizeof(char)))))
					error_management(MALLOC_FAIL, data, -1);
				ft_strncpy(data->file_name, file_name, i);
				ft_strncpy(data->file_name + i, ".cor", 4);
				return (data);
			}
		}
	}
	return (NULL);
}

int			main(int ac, char **av)
{
	int			i;
	t_struct	*data;

	i = 1;
	if (ac < 2)
		error_management(USAGE, NULL, -1);
	while (i < ac)
	{
		if (!(data = change_extension(av[i])))
			error_management(FILE_NAME, NULL, -1);
		else
		{
			is_valid_file(av[i], data);
			instructions_position(data);
			check_labels(data);
			to_bytecode(data);
			ft_printf("file %s was successfully created\n", data->file_name);
			free_data(data);
		}
		i++;
	}
	return (0);
}
