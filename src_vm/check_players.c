/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:01:22 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 22:29:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

int	check_code_size(t_player *player, u_int8_t *code_size_point,
	char **argv, int count)
{
	if ((*((unsigned int *)(code_size_point))) > CHAMP_MAX_SIZE)
	{
		fprintf(stderr, "Error: File %s has \
too large a code (%d bytes > %d bytes)\n",
			*argv, (*((unsigned int *)(code_size_point))), CHAMP_MAX_SIZE);
		free(code_size_point);
		return (1);
	}
	else if ((u_int8_t)count != *(code_size_point))
	{
		fprintf(stderr, "Error: File %s has a code \
size that differ from what its header says\n", *argv);
		free(code_size_point);
		return (1);
	}
	else
	{
		player->player_header.prog_size =
			(*((unsigned int *)(code_size_point)));
		free(code_size_point);
		return (0);
	}
}

int	check_separating_nulls(char *str)
{
	if (str[4 + PROG_NAME_LENGTH] != 0
		| str[5 + PROG_NAME_LENGTH] != 0
		| str[6 + PROG_NAME_LENGTH] != 0
		| str[7 + PROG_NAME_LENGTH] != 0
		| str[12 + PROG_NAME_LENGTH + COMMENT_LENGTH] != 0
		| str[13 + PROG_NAME_LENGTH + COMMENT_LENGTH] != 0
		| str[14 + PROG_NAME_LENGTH + COMMENT_LENGTH] != 0
		| str[15 + PROG_NAME_LENGTH + COMMENT_LENGTH] != 0)
	{
		fprintf(stderr, "Error : mistake in the separating nulls\n");
		return (1);
	}
	return (0);
}

int	check_nulls_and_code_size(int count, char *str,
	t_player *player, char **argv)
{
	int				i;
	int				j;
	unsigned char	*code_size_point;

	i = 139;
	j = 0;
	if (check_separating_nulls(str))
		return (1);
	if (!(code_size_point = (unsigned char *)ft_memalloc(4)))
		return (1);
	while (j < 4)
	{
		code_size_point[j] = str[11 + PROG_NAME_LENGTH - j];
		j++;
	}
	return (check_code_size(player, code_size_point, argv, count));
}

int	check_magic_header(char *str, char **argv, t_player *player)
{
	char helper[4];

	if ((unsigned char)str[0] != 0x00 | (unsigned char)str[1] != 0xea
		| (unsigned char)str[2] != 0x83 | (unsigned char)str[3] != 0xf3)
	{
		fprintf(stderr, "Error: File %s has an invalid header\n", *argv);
		return (1);
	}
	helper[0] = str[3];
	helper[1] = str[2];
	helper[2] = str[1];
	helper[3] = str[0];
	player->player_header.magic = *((unsigned int *)helper);
	return (0);
}
