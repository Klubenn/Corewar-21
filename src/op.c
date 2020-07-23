/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	g_op_tab[17] = {
	{NULL, 0, 0, {0}, 0, 4},
	{"live", 1, 1, {T_DIR}, 0, 4},
	{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{"st", 3, 2, {T_REG, T_IND | T_REG}, 1, 4},
	{"add", 4, 3, {T_REG, T_REG, T_REG}, 1, 4},
	{"sub", 5, 3, {T_REG, T_REG, T_REG}, 1, 4},
	{"and", 6, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"or", 7, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"xor", 8, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
	{"zjmp", 9, 1, {T_DIR}, 0, 2},
	{"ldi", 10, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{"sti", 11, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
	{"fork", 12, 1, {T_DIR}, 0, 2},
	{"lld", 13, 2, {T_DIR | T_IND, T_REG}, 1, 4},
	{"lldi", 14, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
	{"lfork", 15, 1, {T_DIR}, 0, 2},
	{"aff", 16, 1, {T_REG}, 1, 4}
};

t_op	*check_op(char *str)
{
	int		i;
	int		instr_len;
	char	*op;

	instr_len = 0;
	while (ft_isalpha(str[instr_len]) && str[instr_len] != '\0')
		instr_len++;
	if (!(op = ft_strsub(str, 0, instr_len)))
		return (NULL);
	i = 1;
	while (i <= 16)
	{
		if (ft_strcmp(op, g_op_tab[i].name) == 0)
		{
			free(op);
			return (&(g_op_tab[i]));
		}
		i++;
	}
	free(op);
	return (NULL);
}
