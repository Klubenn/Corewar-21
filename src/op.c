
#include <stdio.h>
#include <../libft/libft.h>
#include "../includes/op.h"
#include "../includes/asm.h"

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};


t_op *check_op(char *str)
{
	int		i;
	int		instr_len;
	char	*op;

	i = 0;
	instr_len = 0;

	while (!ft_isspace(str[i]) && str[i] != '\0')
		instr_len++;
	if (!op = ft_strsub(str, 0, instr_len))
		return (NULL);
	while (i < 16)
	{
		if (ft_strcmp(op, op_tab[i].func_num) == 0)
			return (&(op_tab[i]));
		i++;
	}
	return (NULL);
}

void create_instruction(char *str, int instr_pointer, int parametr_pointer, t_struct *data)
{
	t_instruction tmp_data_inst;
	
	tmp_data_inst = data->instruction;
	while (tmp_data_inst != NULL)
		tmp_data_inst = tmp_data_inst->next;
	tmp_data_inst = (t_instruction *)ft_memalloc(sizeof(t_instruction));

	tmp_data_inst->function = check_op(str + instr_pointer);	
	tmp_data_inst->args_of_func = create_args(str + parametr_pointer);
	if (data->label_presence == 1)
	{
		data->label->instruction = tmp_data_inst;
		data->label_present = 0;
	}
}

t_args *create_args(char *str)
{
	t_args *result;
	char **each_arg;
	int i;

	result = (t_args *)ft_memalloc(sizeof(t_args) * 4);
	each_arg = ft_strsplit(str, SEPARATOR_CHAR);
	i = 0;
	while (each_arg[i])
	{
		result[i] = (t_args)ft_memalloc(sizeof(t_args));
		result[i].type = get_type(each_arg[i]);
		result[i]->str = each_arg[i];
		i++;
	}
	return (result);
}

char get_type(char *param)
{
	char *trim_param;

	trim_param = param[skip_spaces(param)];
	if (ft_isdigit(trim_param[0]))
		return (T_IND);
	if (trim_param[0] == 'r' || trim_param[0] == '-')
		return (T_REG);

	if (trim_param[0] == '%')
	{
		if (ft_isdigit(trim_param[1]) || trim_param[1] == '-')
			return (T_DIR);

		if (trim_param[1] == ':')
			return (T_DIR | T_LAB);
	}

	if (trim_param[0] == ':')
		return (T_IND | T_LAB);
}