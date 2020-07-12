#include "../includes/asm.h"

void	write_backwards(int fd, void *source, int size)
{
	char *c;

	c = (char *)source;
	while (--size >= 0)
		write(fd, c + size, 1);
}

void	bin_magic(int fd)
{
	int x = COREWAR_EXEC_MAGIC;

	write_backwards(fd, &x, sizeof(int));
}

void bin_champ_name(int fd, t_struct *data)
{
	char *name;

	name = (char *)ft_memalloc(PROG_NAME_LENGTH);
	if (data->name && name)
		ft_strcpy(name, data->name);
	write(fd, name, PROG_NAME_LENGTH);
	free(name);
}

void bin_null(int fd)
{
	int x = 0;

	write(fd, &x, 4);
}

void	bin_exec_code_size(int fd, t_struct *data)
{
	int size;

	size = data->code_length;
	write_backwards(fd, &size, sizeof(int));
}

void	bin_comment(int fd, t_struct *data)
{
	char *comment;

	comment = (char *)ft_memalloc(COMMENT_LENGTH * sizeof(char));
	if (data->comment)
		ft_strcpy(comment, data->comment);
	write(fd, comment, COMMENT_LENGTH);
}


void    to_bytecode(t_struct *data)
{
	int fd;

	fd = open(data->file_name, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0644);
	bin_magic(fd);
	bin_champ_name(fd, data);
	bin_null(fd);
	bin_exec_code_size(fd, data);
	bin_comment(fd, data);
	bin_null(fd);
	bin_exec_champ(fd, data);
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
		size += instruction->args_of_func[num]->type == T_DIR ? op_data->t_dir_size : 0;
		size += instruction->args_of_func[num]->type == T_IND ? 2 : 0;
		size += instruction->args_of_func[num]->type == T_REG ? 1 : 0;
		size_total += size;
		instruction->args_of_func[num]->size = size;
	}
	size_total += op_data->arg_type_code + 1;
	return (size_total);
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
		name = label_1->label_name;
		label_2 = label_1->next;
		while (label_2)
		{
			if (ft_strcmp(name, label_2->label_name) == 0)
				error_management(DUPL_LABEL, data);
			label_2 = label_2->next;
		}
		label_1 = label_1->next;
	}
}