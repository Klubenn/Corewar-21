
#include <stdio.h>
#include <../libft/libft.h>
#include "../includes/op.h"
#include "../includes/asm.h"

t_op    op_tab[17] =
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


t_op *check_op(char *str)
{
	int		i;
	int		instr_len;
	char	*op;

	instr_len = 0;
	while (!ft_isspace(str[instr_len]) && str[instr_len] != '\0')
		instr_len++;
	if (!(op = ft_strsub(str, 0, instr_len)))
		return (NULL);
	i = 1;
	while (i <= 16)
	{
		if (ft_strcmp(op, op_tab[i].name) == 0)
			return (&(op_tab[i]));
		i++;
	}
	return (NULL);
}

int create_instruction(t_op *op, char *str, t_struct *data)
{
	t_instruction *tmp_data_inst;
	
	tmp_data_inst = data->instruction;
	while (tmp_data_inst->next != NULL)
		tmp_data_inst = tmp_data_inst->next;
	if (!(tmp_data_inst->next = (t_instruction *)ft_memalloc(sizeof(t_instruction))))
		return (MALLOC_FAIL);
	tmp_data_inst->next->function = op->func_num;
	tmp_data_inst->next->args_of_func = create_args(str);
	if (data->label_present == 1)
	{
		data->label->instruction = tmp_data_inst;
		data->label_present = 0;
	}
}

t_args **create_args(char *str)
{
	t_args **result;
	char **each_arg;
	int i;

	result = (t_args **)ft_memalloc(sizeof(t_args) * 4);
	each_arg = ft_strsplit(str, SEPARATOR_CHAR);
	i = 0;
	while (each_arg[i])
	{
		result[i] = (t_args *)ft_memalloc(sizeof(t_args));
		result[i]->type = get_type(each_arg[i]);
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
