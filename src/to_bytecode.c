#include "../includes/asm.h"

void	write_to_array(char *ptr, char c)
{
	*ptr = c;
}

void	write_to_file(t_struct *data, int fd)
{
	write(fd, data->file_arr_start, data->file_size);
}

void	write_backwards(t_struct *data, void *source, int size)
{
	char *c;

	c = (char *)source;
	while (--size >= 0)
	{
		write_to_array(data->file_arr, *(c + size));
		(data->file_arr)++;
	}
}

void	bin_magic(t_struct *data)
{
	int x = COREWAR_EXEC_MAGIC;

	write_backwards(data, &x, sizeof(int));
}

void bin_champ_name(t_struct *data)
{
	char	*name;
	int 	len;

	name = (char *)ft_memalloc(PROG_NAME_LENGTH * sizeof(char));
	if (data->name)
		ft_strcpy(name, data->name);
	len = 0;
	while (len < PROG_NAME_LENGTH)
	{
		write_to_array(data->file_arr, *name);
		name++;
		(data->file_arr)++;
		len++;
	}
}

void bin_null(t_struct *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		write_to_array(data->file_arr, (char)0);
		(data->file_arr)++;
		i++;
	}
}

void	bin_exec_code_size(t_struct *data)
{
	int size;

	size = data->code_length;
	write_backwards(data, &size, sizeof(int));
}

void	bin_comment(t_struct *data)
{
	char	*comment;
	int 	len;

	comment = (char *)ft_memalloc(COMMENT_LENGTH * sizeof(char));
	if (data->comment)
		ft_strcpy(comment, data->comment);
	len = 0;
	while (len < COMMENT_LENGTH)
	{
		write_to_array(data->file_arr, *comment);
		comment++;
		(data->file_arr)++;
		len++;
	}
}

void    to_bytecode(t_struct *data)
{
	int fd;

	data->file_size = 16 + PROG_NAME_LENGTH + COMMENT_LENGTH + data->code_length;
	if (!(data->file_arr = (char *)ft_memalloc(sizeof(char) * data->file_size)))
		error_management(MALLOC_FAIL, data, 0);
	data->file_arr_start = data->file_arr;
	bin_magic(data);
	bin_champ_name(data);
	bin_null(data);
	bin_exec_code_size(data);
	bin_comment(data);
	bin_null(data);
	bin_exec_champ(data);
	fd = open(data->file_name, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0644);
	write_to_file(data, fd);
	close(fd);
}



int		argument_size(t_instruction *instruction)
{
	t_op	*op_data;
	int 	num;
	int 	size;
	int 	size_total;

	size_total = 0;
	op_data = instruction->op;
	num = op_data->arg_num;
	while (num-- > 0)
	{
		size = 0;
		size += (instruction->args_of_func[num]->type & T_DIR) ? op_data->t_dir_size : 0;
		size += (instruction->args_of_func[num]->type & T_IND) ? 2 : 0;
		size += (instruction->args_of_func[num]->type & T_REG) ? 1 : 0;
		size_total += size;
		instruction->args_of_func[num]->size = size;
	}
	size_total += op_data->arg_type_code + 1;
	return (size_total);
}

t_instruction *create_empty_instruction(t_struct *data)
{
	t_instruction *instruction;

	instruction = data->instruction;
	while (instruction->next)
		instruction = instruction->next;
	if (!(instruction->next = (t_instruction *)ft_memalloc(sizeof(t_instruction))))
		return (NULL);
	instruction->next->position = instruction->position + argument_size(instruction);
	return (instruction->next);
}

void	change_type(t_instruction *instruction)
{
	int 	num;

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

void	instructions_position(t_struct *data)
{
	t_instruction *instruction;
	int position;

	position = 0;
	instruction = data->instruction;
	while(instruction)
	{
		instruction->position = position;
		position += argument_size(instruction);
		change_type(instruction);
		instruction = instruction->next;
	}
	data->code_length = position;
}

void	check_labels(t_struct *data)
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
				label_2->instruction = label_1->instruction;
			if (ft_strcmp(name, label_2->label_name) == 0)
				error_management(DUPL_LABEL, data, label_1->instruction->line);
			label_2 = label_2->next;
		}
		label_1 = label_1->next;
	}
}