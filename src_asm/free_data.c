/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_error_message(enum e_err_message num)
{
	static char *ch[] = {NULL,
			"usage: ./asm file_name\n",
			"Wrong file name. Should have an \".s\" extension.\n",
			"Syntax error - unexpected end of input. Missing end of line.\n",
			"Can't open the file.\n",
			"Name and comment should be at the top of file.\n",
			"Only a name or a comment can begin with a \'.\'\n",
			"Memory allocation failed.\n",
			"Champion name is too long.\n",
			"Champion comment is too long.\n",
			"Name and comment should start with the quotes.\n",
			"Name and comment should end with the quotes.\n",
			"Syntax error.\n",
			"Wrong register number.\n",
			"Wrong number.\n",
			"Error: duplicate labels.\n",
			"File doesn't exist.\n",
			"Multiple champion names.\n",
			"Multiple champion comments.\n",
			"Label not found.\n",
			"Incorrect argument.\n",
			"Can't create file. Access to location denied.\n"
	};

	ft_putstr_fd(ch[num], 2);
}

void	free_instruction(t_instruction *instruction)
{
	t_instruction *tmp;

	while (instruction)
	{
		tmp = instruction->next;
		if (instruction->args_of_func)
		{
			while ((instruction->num_of_args)--)
			{
				free(instruction->args_of_func[instruction->num_of_args]->str);
				free(instruction->args_of_func[instruction->num_of_args]);
			}
			free(instruction->args_of_func);
		}
		free(instruction);
		instruction = tmp;
	}
}

void	free_label(t_label *label)
{
	t_label *tmp;

	tmp = label;
	while (label)
	{
		label = label->next;
		free(tmp->label_name);
		free(tmp);
		tmp = label;
	}
}

void	free_data(t_struct *data)
{
	if (data->instruction)
		free_instruction(data->instruction);
	if (data->label)
		free_label(data->label);
	free(data->file_name);
	free(data->name);
	free(data->comment);
	free(data->gnl_buf);
	free(data->file_arr_start);
	free(data);
}

void	error_management(int err, t_struct *data, int line_num)
{
	int				line;
	t_instruction	*instruction;

	if (data)
	{
		line = data->line;
		if (line_num)
		{
			instruction = data->instruction;
			while (instruction->next && instruction->line != line_num)
				instruction = instruction->next;
			line = line_num;
		}
		ft_printf("Error on line %d: %z", line, 2);
		print_error_message(err);
		free_data(data);
	}
	else
		print_error_message(err);
	exit(-1);
}
