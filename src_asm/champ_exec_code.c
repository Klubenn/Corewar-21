/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_exec_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	bin_champ_name(t_struct *data)
{
	char	*name;
	int		len;

	if (!(name = (char *)ft_memalloc((PROG_NAME_LENGTH + 1) * sizeof(char))))
		error_management(MALLOC_FAIL, data, 0);
	if (data->name)
		ft_strcpy(name, data->name);
	len = 0;
	while (len < PROG_NAME_LENGTH)
	{
		write_to_array(data->file_arr, name[len]);
		(data->file_arr)++;
		len++;
	}
	free(name);
}

void	bin_comment(t_struct *data)
{
	char	*comment;
	int		len;

	if (!(comment = (char *)ft_memalloc((COMMENT_LENGTH + 1) * sizeof(char))))
		error_management(MALLOC_FAIL, data, 0);
	if (data->comment)
		ft_strcpy(comment, data->comment);
	len = 0;
	while (len < COMMENT_LENGTH)
	{
		write_to_array(data->file_arr, comment[len]);
		(data->file_arr)++;
		len++;
	}
	free(comment);
}

void	argument_type(t_struct *data, t_instruction *instruction)
{
	unsigned char	arg_num[4];
	unsigned char	arg_type;
	int				i;

	arg_type = 0;
	i = 0;
	while (i < instruction->num_of_args)
	{
		arg_num[i] = instruction->args_of_func[i]->type;
		if (arg_num[i] & T_LAB)
			arg_num[i] -= T_LAB;
		arg_num[i] = arg_num[i] << (6 - 2 * i);
		arg_type = arg_type | arg_num[i];
		i++;
	}
	write_to_array(data->file_arr, arg_type);
	(data->file_arr)++;
}

void	operation_code(t_struct *data, t_instruction *instruction)
{
	char	op_code;

	op_code = (char)instruction->function;
	write_to_array(data->file_arr, op_code);
	(data->file_arr)++;
	if (op_code != 1 && op_code != 9 && op_code != 12 && op_code != 15)
		argument_type(data, instruction);
}

void	bin_exec_champ(t_struct *data)
{
	t_instruction *instruction;

	instruction = data->instruction;
	while (instruction && instruction->function)
	{
		operation_code(data, instruction);
		arguments_code(data, instruction);
		instruction = instruction->next;
	}
}
