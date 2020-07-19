#include "asm.h"

void	print_error_message(enum err_message num)
{
	static char *ch[] = {
			NULL,
			"usage: ./asm file_name\n",											//USAGE
			"Wrong file name. Should have an \".s\" extension.\n",				//FILE_NAME
			"Syntax error - unexpected end of input. Missing end of line.\n",	//END_INPUT
			"Can't open the file.\n",											//NO_FILE
			"Name and comment should be at the top of file.\n",					//TOP_FILE
			"Only a name or a comment can begin with a \'.\'\n",				//DOT_START
			"Memory allocation failed.\n",										//MALLOC_FAIL
			"Champion name is too long.\n",										//LONG_NAME
			"Champion comment is too long.\n",									//LONG_COMM
			"Name and comment should start with the quotes.\n",					//QUOTES_BEGIN
			"Name and comment should end with the quotes.\n",					//QUOTES_END
			"Syntax error.\n",													//SYNTAX_ERROR
			"Wrong register number.\n",											//WRONG_REG
			"Wrong number.\n",													//WRONG_NUM
			"Error: duplicate labels.\n",										//DUPL_LABEL
			"File doesn't exist.\n",											//NOT_EXIST
			"Multiple champion names.\n",										//MULTIPLE_NAME
			"Multiple champion comments.\n",									//MULTIPLE_COMMENT

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
	free(data);
}

void	error_management(int err, t_struct *data)
{
	if (err)
	{
		if (data)
		{
			ft_putstr_fd("Error on line ", 2);
			ft_putnbr_fd(data->line, 2);
			ft_putstr_fd(": ", 2);
		}
		print_error_message(err);
		if (data->str)
			ft_putendl_fd(data->str, 2);
	}
	if (data)
		free_data(data);
	exit(1);
}
