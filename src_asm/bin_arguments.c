/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			bin_find_label(t_struct *data, char *label_from_instruc)
{
	t_label	*label;

	label = data->label;
	while (label)
	{
		if (ft_strcmp(label->label_name, label_from_instruc) == 0)
			return (label->instruction->position);
		label = label->next;
	}
	return (-1);
}

void		f_reg(t_struct *data, t_instruction *instruction, t_args *argument)
{
	char	reg_num;
	int		error;

	error = corewar_atoi((argument->str) + 1, &reg_num, sizeof(char), 0);
	if (!error)
	{
		write_to_array(data->file_arr, reg_num);
		(data->file_arr)++;
	}
	else
		error_management(WRONG_REG, data, instruction->line);
}

void		f_dir(t_struct *data, t_instruction *instruction, t_args *argument)
{
	int	dir_num;
	int	position;

	dir_num = (int)(-1 * instruction->position);
	if (*(argument->str + 1) == LABEL_CHAR)
	{
		position = bin_find_label(data, argument->str + 2);
		if (position == -1)
			error_management(LABEL_NOT_FOUND, data, instruction->line);
		dir_num += position;
		write_backwards(data, &dir_num, argument->size);
	}
	else
	{
		if (corewar_atoi(argument->str + 1, &dir_num, argument->size, 0))
			error_management(WRONG_NUM, data, instruction->line);
		write_backwards(data, &dir_num, argument->size);
	}
}

void		f_ind(t_struct *data, t_instruction *instruction, t_args *argument)
{
	short	ind_num;
	int		position;

	ind_num = (short)(-1 * instruction->position);
	if (*(argument->str) == LABEL_CHAR)
	{
		position = (short)bin_find_label(data, argument->str + 1);
		if (position == -1)
			error_management(LABEL_NOT_FOUND, data, instruction->line);
		ind_num += position;
		write_backwards(data, &ind_num, sizeof(short));
	}
	else
	{
		if (corewar_atoi(argument->str, &ind_num, IND_SIZE, 0))
			error_management(WRONG_NUM, data, instruction->line);
		write_backwards(data, &ind_num, sizeof(short));
	}
}

void		arguments_code(t_struct *data, t_instruction *instruction)
{
	int i;

	i = 0;
	while (i < instruction->num_of_args)
	{
		if (instruction->args_of_func[i]->type == REG_CODE)
			f_reg(data, instruction, instruction->args_of_func[i]);
		else if (instruction->args_of_func[i]->type == DIR_CODE)
			f_dir(data, instruction, instruction->args_of_func[i]);
		else if (instruction->args_of_func[i]->type == IND_CODE)
			f_ind(data, instruction, instruction->args_of_func[i]);
		i++;
	}
}
