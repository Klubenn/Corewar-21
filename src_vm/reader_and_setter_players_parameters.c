/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_and_setter_players_parameters.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:08:58 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/26 18:12:32 by vladimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void	read_code(char *str, t_player *player, int count)
{
	int i;

	i = 0;
	str = str + 2192;
	player->code = (unsigned char *)ft_memalloc(count);
	while ((u_int32_t)i < player->player_header.prog_size)
	{
		player->code[i] = str[i];
		i++;
	}
}

void	read_comment(char *str, t_player *player)
{
	int i;

	i = 0;
	while (i < COMMENT_LENGTH)
	{
		player->player_header.comment[i] = str[i + 12 + PROG_NAME_LENGTH];
		i++;
	}
}

void	set_player_name(char *str, t_player *player)
{
	int i;

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		player->player_header.prog_name[i] = str[i + 4];
		i++;
	}
	player->player_header.prog_name[PROG_NAME_LENGTH] = '\0';
}

int		players_reader_parse_champions(int fd, t_player *player, char **argv)
{
	char	str[BUFFER_SIZE];
	int		c;
	int		count;

	count = 0;
	while ((c = read(fd, str, BUFFER_SIZE)))
		count = count + c;
	count = count - PROG_NAME_LENGTH - COMMENT_LENGTH - 16;
	lseek(fd, 0, SEEK_SET);
	read(fd, str, BUFFER_SIZE);
	if (check_magic_header(str, argv, player))
		return (1);
	set_player_name(str, player);
	if (check_nulls_and_code_size(count, str, player, argv) == 0)
	{
		read_comment(str, player);
		read_code(str, player, count);
		return (0);
	}
	return (1);
}
