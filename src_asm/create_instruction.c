/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	push_back(t_struct *data, t_instruction *instruction)
{
	t_instruction *instr;

	instr = data->instruction;
	if (!instr)
		data->instruction = instruction;
	else
	{
		while (instr->next)
			instr = instr->next;
		instr->next = instruction;
	}
}

void	put_instruction_to_label(t_struct *data, t_instruction *instruction)
{
	t_label			*label;

	label = data->label;
	while (label)
	{
		if (!label->instruction)
			label->instruction = instruction;
		label = label->next;
	}
	data->label_present = 0;
}

int		create_instruction(t_op *op, char **params, t_struct *data)
{
	t_instruction	*instruction;

	if (!(instruction = (t_instruction *)ft_memalloc(sizeof(t_instruction))) ||
	!(instruction->args_of_func = (t_args **)ft_memalloc(sizeof(t_args *) * 4)))
	{
		free_arr(params);
		return (MALLOC_FAIL);
	}
	instruction->op = op;
	instruction->num_of_args = op->arg_num;
	instruction->function = op->func_num;
	if (!(create_args(instruction->args_of_func, params)))
	{
		free_arr(params);
		return (SYNTAX_ERROR);
	}
	if (data->label_present == 1)
		put_instruction_to_label(data, instruction);
	push_back(data, instruction);
	return (0);
}

int		create_args(t_args **args_of_func, char **params)
{
	int				i;
	unsigned char	type;

	i = 0;
	while (params[i])
	{
		if (!(args_of_func[i] = (t_args *)ft_memalloc(sizeof(t_args))) ||
			!(type = get_type(params[i])))
			return (0);
		args_of_func[i]->type = type;
		if (check_ending(params[i] + skip_word(params[i])))
			return (0);
		args_of_func[i]->str = params[i];
		i++;
	}
	free(params);
	return (1);
}
