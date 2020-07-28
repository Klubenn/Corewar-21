/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int						put_data_to_instruc(t_struct *data, int error)
{
	t_instruction *instruction;

	if (data->instruction)
	{
		instruction = data->instruction;
		while (instruction->next)
			instruction = instruction->next;
		if (!instruction->line)
			instruction->line = data->line;
	}
	return (error);
}

void					process_string(char *str, t_struct *data, int fd)
{
	int		error;
	char	*str_trim;

	str_trim = trim_start(str);
	if (!*str_trim || *str_trim == COMMENT_CHAR)
		return ;
	if (*str_trim == '.')
	{
		if (ft_strnequ(str, NAME_CMD_STRING, 5))
			error = MULTIPLE_NAME;
		else if (ft_strnequ(str, COMMENT_CMD_STRING, 8))
			error = MULTIPLE_COMMENT;
		else
			error = DOT_START;
	}
	else
		error = put_data_to_instruc(data, check_other_strings(str_trim, data));
	if (error)
	{
		free(str);
		close(fd);
		error_management(error, data, 0);
	}
}

static t_instruction	*create_empty_instruction(t_struct *data)
{
	t_instruction *instruction;

	instruction = data->instruction;
	while (instruction->next)
		instruction = instruction->next;
	if (!(instruction->next =
			(t_instruction *)ft_memalloc(sizeof(t_instruction))))
		return (NULL);
	instruction->next->position = instruction->position +
							argument_size(instruction);
	return (instruction->next);
}

static t_instruction	*find_empty_instruction(t_struct *data)
{
	t_instruction *instruction;

	instruction = data->instruction;
	while (instruction)
	{
		if (!instruction->function)
			return (instruction);
		if (!instruction->next)
			return (create_empty_instruction(data));
		instruction = instruction->next;
	}
	return (create_empty_instruction(data));
}

void					check_labels(t_struct *data)
{
	t_label *label_1;
	t_label *label_2;
	char	*name;

	label_1 = data->label;
	while (label_1)
	{
		if (!label_1->instruction)
			label_1->instruction = create_empty_instruction(data);
		name = label_1->label_name;
		label_2 = label_1->next;
		while (label_2)
		{
			if (!label_2->instruction)
				label_2->instruction = find_empty_instruction(data);
			if (ft_strcmp(name, label_2->label_name) == 0)
				error_management(DUPL_LABEL, data, label_1->instruction->line);
			label_2 = label_2->next;
		}
		label_1 = label_1->next;
	}
}
