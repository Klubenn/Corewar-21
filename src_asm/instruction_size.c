/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/24 23:10:46 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			change_type(t_instruction *instruction)
{
	int num;

	num = instruction->num_of_args;
	while (num-- > 0)
	{
		if (instruction->args_of_func[num]->type & T_DIR)
			instruction->args_of_func[num]->type = DIR_CODE;
		else if (instruction->args_of_func[num]->type & T_REG)
			instruction->args_of_func[num]->type = REG_CODE;
		else if (instruction->args_of_func[num]->type & T_IND)
			instruction->args_of_func[num]->type = IND_CODE;
	}
}

int				argument_size(t_instruction *instruction)
{
	t_op	*op_data;
	int		num;
	int		size;
	int		size_total;

	size_total = 0;
	op_data = instruction->op;
	num = op_data->arg_num;
	while (num-- > 0)
	{
		size = 0;
		size += (instruction->args_of_func[num]->type & T_DIR) ?
				op_data->t_dir_size : 0;
		size += (instruction->args_of_func[num]->type & T_IND) ? 2 : 0;
		size += (instruction->args_of_func[num]->type & T_REG) ? 1 : 0;
		size_total += size;
		instruction->args_of_func[num]->size = size;
	}
	size_total += op_data->arg_type_code + 1;
	return (size_total);
}

void			instructions_position(t_struct *data)
{
	t_instruction	*instruction;
	int				position;

	position = 0;
	instruction = data->instruction;
	while (instruction)
	{
		instruction->position = position;
		position += argument_size(instruction);
		change_type(instruction);
		instruction = instruction->next;
	}
	data->code_length = position;
}
