#include "../includes/asm.h"

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

int 	bin_find_label(t_struct *data, char *label_from_instruc)
{
	t_label	*label;

	label = data->label;
	while (label)
	{
		if (strcmp(label->label_name, label_from_instruc) == 0)
			return (label->instruction->position);
		label = label->next;
	}
	return (-1);
}

int		corewar_atoi(char *arg, void *numptr, int size)
{
	long long	result;
	int 		sign;
	int 		digits;
	int 		*num;

	sign = 1;
	digits = 0;
	result = 0;
	if (!arg || !*arg)
		return (1);
	if (*arg == '-')
	{
		sign = -1;
		arg++;
	}
	while(*arg >= '0' && *arg <= '9' && digits <= 10)
	{
		result = result * 10 + (*arg - '0');
		digits = result == 0 ? 1 : digits + 1;
		arg++;
	}
	result *= sign;
	if (*arg || digits > 10 || (size == 2 && (result > SHRT_MAX || result < SHRT_MIN))
		|| (size == 4 && (result > INT_MAX || result < INT_MIN)) || (size == 1 &&
		(result < 1 || result > REG_NUMBER)))
		return (1);
	num = numptr;
	*num = size == 1 ? (char)result : *num;
	*num = size == 2 ? (short)result : *num;
	*num = size == 4 ? (int)result : *num;
	return (0);
}

void	f_reg(t_struct *data, t_instruction *instruction, t_args *argument)
{
	char	reg_num;
	int		error;

	error = (unsigned char)corewar_atoi((argument->str) + 1, &reg_num, sizeof(char));
	if (!error)
	{
		write_to_array(data->file_arr, reg_num);
		(data->file_arr)++;
	}
	else
		error_management(WRONG_REG, data, instruction->line);
}

void	f_dir(t_struct *data, t_instruction *instruction, t_args *argument)
{
	int		dir_num;
	int 	position;

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
		if (corewar_atoi(argument->str + 1, &dir_num, argument->size))
			error_management(WRONG_NUM, data, instruction->line);
		write_backwards(data, &dir_num, argument->size);
	}
}

void	f_ind(t_struct *data, t_instruction *instruction, t_args *argument)
{
	short	ind_num;
	int 	position;

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
		if (corewar_atoi(argument->str, &ind_num, IND_SIZE))
			error_management(WRONG_NUM, data, instruction->line);
		write_backwards(data, &ind_num, sizeof(short));
	}
}

void arguments_code(t_struct *data, t_instruction *instruction)
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

void	bin_exec_champ(t_struct *data)
{
	t_instruction *instruction;

	instruction = data->instruction;
	while (instruction)
	{
		operation_code(data, instruction);
		arguments_code(data, instruction);
		instruction = instruction->next;
	}
}