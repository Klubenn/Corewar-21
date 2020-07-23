/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_reg(char *param)
{
	int reg;

	if (!param || !param[0] || param[0] != 'r' || !ft_isdigit(param[1]))
		return (0);
	reg = ft_atoi(param + 1);
	if (reg > 0 && reg <= REG_NUMBER)
		return (1);
	return (0);
}

int		check_param_correctness(unsigned char type, char *param)
{
	if (type & T_DIR)
	{
		if (!param || !param[0] || !param[1])
			return (0);
		if (type & T_LAB)
			return (1);
		if (ft_strlen(param) >= 3 && param[1] == '-' && ft_isdigit(param[2]))
			return (1);
		if (ft_isdigit(param[1]))
			return (1);
	}
	else if (type & T_IND)
	{
		if (!param || !param[0])
			return (0);
		if (type & T_LAB)
			return (1);
		if (ft_strlen(param) >= 2 && ft_isdigit(param[1]) && param[0] == '-')
			return (1);
		if (ft_isdigit(param[0]))
			return (1);
	}
	else if (type & T_REG)
		return (check_reg(param));
	return (0);
}

int		check_params(char **params, t_op *op)
{
	unsigned char	type;
	char			*param;
	int				i;

	i = 0;
	while (i < op->arg_num)
	{
		param = params[i];
		type = get_type(param);
		if (!(type & op->arg[i]) || !check_param_correctness(type, param))
			return (0);
		i++;
	}
	return (1);
}

int		check_params_num(char **params, int needed_num)
{
	int i;

	i = 0;
	while (params[i])
		i++;
	return ((i == needed_num) ? 1 : 0);
}

int		check_param(t_struct *data, char *str, t_op *op)
{
	char **params;

	if (!(params = split_corewar(str)))
		return (INCORRECT_ARGUMENT);
	if (!(check_params_num(params, op->arg_num) && check_params(params, op)))
	{
		free_arr(params);
		return (SYNTAX_ERROR);
	}
	else
		return (create_instruction(op, params, data));
}
