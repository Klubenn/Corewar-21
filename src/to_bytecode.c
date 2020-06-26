#include "../includes/asm.h"

void	write_backwards(int fd, void *source, int size)
{
	char *c;

	c = (char *)source;
	while (--size >= 0)
		write(fd, c, 1);
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


void    to_bytecode(char *new_file, t_struct *data)
{
	int fd;

	fd = open(new_file, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0644);
	bin_magic(fd);
	bin_champ_name(fd, data);
	bin_null(fd);
	bin_exec_code_size(fd, data);
	bin_comment(fd, data);
	bin_null(fd);
//	bin_exec_champ(fd, data);
	close(fd);
}


t_op	op_calc(int num) //TODO наверное, лучше это просто сделать глобальным массивом, а не ф-цией
{
	static t_op    op_tab[17] =
			{
					{NULL,0, 0, {0}, 0, 4},
					{"live", 1, 1, {T_DIR}, 0, 4},
					{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 1, 4},
					{"st", 3, 2, {T_REG, T_IND | T_REG}, 1, 4},
					{"add", 4, 3, {T_REG, T_REG, T_REG}, 1, 4},
					{"sub", 5, 3, {T_REG, T_REG, T_REG}, 1, 4},
					{"and", 6, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
					{"or", 7, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
					{"xor", 8, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
					{"zjmp", 9, 1, {T_DIR}, 0, 2},
					{"ldi", 10, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
					{"sti", 11, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
					{"fork", 12, 1, {T_DIR}, 0, 2},
					{"lld", 13, 2, {T_DIR | T_IND, T_REG}, 1, 4},
					{"lldi", 14, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
					{"lfork", 15, 1, {T_DIR}, 0, 2},
					{"aff", 16, 1, {T_REG}, 1, 4}
			};
	return (op_tab[num]);
}

int		argument_size(t_instruction *instruction)
{
	t_op	op_data;
	int 	num;
	int 	size;
	int 	size_total;

	size_total = 0;
	op_data = op_calc(instruction->function);
	num = op_data.arg_num;
	while (num-- > 0)
	{
		size = 0;
		size += instruction->args_of_func[num]->type == T_DIR ? op_data.t_dir_size : 0;
		size += instruction->args_of_func[num]->type == T_IND ? 2 : 0;
		size += instruction->args_of_func[num]->type == T_REG ? 1 : 0;
		size_total += size;
		instruction->args_of_func[num]->size = size;
	}
	size_total += op_data.arg_type_code + 1;
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
				exit (1);//invoke error function
			label_2 = label_2->next;
		}
		label_1 = label_1->next;
	}
}