/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_allocator_for_cmd_line_arguments.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:24:36 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

size_t	ft_count_words(char const *s, char c)
{
	size_t words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

void	memory_allocator_helper_1(char **buff_2, char **buff,
	char **buff_begin)
{
	int i;
	int j;

	j = 0;
	while (buff_2[j] != 0)
	{
		i = 0;
		if (!(*buff = (char *)ft_memalloc(sizeof(char) *
			(ft_strlen(buff_2[j]) + 1))))
		{
			arguments_memory_deleter(buff_begin);
			arguments_memory_deleter(buff_2);
			perror("Error");
			exit(1);
		}
		while (buff_2[j][i] != 0)
		{
			(*buff)[i] = buff_2[j][i];
			i++;
		}
		(*buff)[i] = 0;
		j++;
		buff++;
	}
}

void	memory_allocator_helper(char *str, char **buff)
{
	char **buff_begin;
	char **buff_2;

	buff_begin = buff;
	while (*buff != 0)
		buff++;
	if (!(buff_2 = ft_strsplit(str, ' ')))
	{
		arguments_memory_deleter(buff);
		perror("Error");
		exit(1);
	}
	memory_allocator_helper_1(buff_2, buff,
		buff_begin);
	arguments_memory_deleter(buff_2);
}

void	arguments_memory_deleter(char **argv)
{
	char **begin;

	begin = argv;
	while (*argv)
	{
		free(*argv);
		argv++;
	}
	free(*argv);
	free(begin);
}

char	**memory_allocator_cmd_line_args(char **argv)
{
	int			counter;
	int			i;
	char		**buff;

	i = 0;
	counter = 0;
	while (argv[i] != 0)
	{
		counter += ft_count_words(argv[i], ' ');
		i++;
	}
	if (!(buff = (char **)ft_memalloc(sizeof(char *) * (counter + 1))))
	{
		perror("Error");
		exit(1);
	}
	i = 0;
	while (argv[i] != 0)
	{
		memory_allocator_helper(argv[i], buff);
		i++;
	}
	return (buff);
}
