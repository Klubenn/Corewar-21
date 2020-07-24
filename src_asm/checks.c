/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_other_strings(char *str, t_struct *data)
{
	t_op	*op;
	int		if_label;
	char	*cut_str;
	int		result;

	if ((if_label = check_label(data, str)) < 0)
		return (MALLOC_FAIL);
	if (!check_ending(str + if_label))
		return (0);
	if (!(cut_str = cut_string(str + if_label)))
		return (MALLOC_FAIL);
	if (!(op = check_op(cut_str)))
	{
		free(cut_str);
		return (SYNTAX_ERROR);
	}
	str = trim_start(cut_str + ft_strlen(op->name));
	result = check_param(data, str, op);
	free(cut_str);
	return (result);
}

void	free_strings(char *str1, char *str2, char *str3, char *str4)
{
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

char	get_type(char *param)
{
	char *trim_param;

	trim_param = param + skip_spaces(param);
	if (ft_isdigit(trim_param[0]) || trim_param[0] == '-')
		return (T_IND);
	if (trim_param[0] == 'r')
		return (T_REG);
	if (trim_param[0] == DIRECT_CHAR)
	{
		if (ft_isdigit(trim_param[1]) || trim_param[1] == '-')
			return (T_DIR);
		if (trim_param[1] == LABEL_CHAR)
			return (T_DIR | T_LAB);
	}
	if (trim_param[0] == LABEL_CHAR)
		return (T_IND | T_LAB);
	return (0);
}

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
