
#include <stdio.h>
#include <../libft/libft.h>
#include "../includes/op.h"
#include "../includes/asm.h"

int skip_spaces(char* str)
{
    int i;

    i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int skip_word(char* str)
{
    int i;

    i = 0;
    while (!ft_isspace(str[i]) && str[i] != '\0') // !
		i++;
    return (i);
}

int check_params_num(char **params, int needed_num)
{
	int i;

	i = 0;
	while (params[i])
		i++;
	return ((i == needed_num) ? 1 : 0);
}

int check_reg(char *param)
{
    int reg;

    if (!param || !param[0] || param[0] != 'r' || !ft_isdigit(param[1]))
        return (0);
    reg = ft_atoi(param + 1);
    if (reg > 0 && reg <= REG_NUMBER)
        return (1);
    return (0);
}

int check_param_correctness(unsigned char type, char* param)
{
    if (type & T_DIR)
    {
        if (!param || !param[0] || !param[1])
            return (0);
        if (type & T_LAB)
            return (1);
        if (ft_strlen(param) >= 3 && param[1] == '-' && ft_isdigit(param[2]))
            return (1);
        if (ft_isdigit(param[1]))
            return (1);
    }
    else if (type & T_IND)
    {
        if (!param || !param[0])
            return (0);
        if (type & T_LAB)
            return (1);
        if (ft_strlen(param) >= 2 && ft_isdigit(param[1]) && param[0] == '-')
            return (1);
        if (ft_isdigit(param[0]))
            return (1);
    }
    else if (type & T_REG)
        return check_reg(param);
    return 0;
}

int check_params(char **params, t_op *op)
{
    unsigned char type;
    char *param;
    int i;

    i = 0;
    while (i < op->arg_num)
    {
        param = params[i];
        type = get_type(param);
        if (!(type & op->arg[i]) || !check_param_correctness(type, param))
            return (0);
        i++;
    }
    return (1);
}

char get_type(char *param)
{
    char *trim_param;

    trim_param = param + skip_spaces(param);
    if (ft_isdigit(trim_param[0]))
        return (T_IND);
    if (trim_param[0] == 'r' || trim_param[0] == '-')
        return (T_REG);

    if (trim_param[0] == DIRECT_CHAR)
    {
        if (ft_isdigit(trim_param[1]) || trim_param[1] == '-')
            return (T_DIR);

        if (trim_param[1] == ':')
            return (T_DIR | T_LAB);//todo remove T_LAB
    }

    if (trim_param[0] == ':')
        return (T_IND | T_LAB);//todo remove T_LAB
    return (0);//TODO проверить, может ли быть ошибка, если да, то какой ретюрн
}


void free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int check_param(t_struct *data, char *str, t_op *op)// str2 already starts with word! not contains comments
{
	char **params;

	if (!(params = split_corewar(str)))
	    return (MALLOC_FAIL);
	if (!(check_params_num(params, op->arg_num) && check_params(params, op)) )
	{
        free_arr(params);
        return (SYNTAX_ERROR);
    }
	else
        return (create_instruction(op, params, data));
}

void push_back(t_struct *data, t_instruction *instruction)
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

int create_instruction(t_op *op, char **params, t_struct *data)
{
    t_instruction *instruction;
    t_label *label;

    if (!(instruction = (t_instruction *)ft_memalloc(sizeof(t_instruction)))
        || !(instruction->args_of_func = (t_args	**)ft_memalloc(sizeof(t_args *) * 4)))
        return (MALLOC_FAIL);

    instruction->op = op;
    instruction->num_of_args = op->arg_num;
	instruction->function = op->func_num;
	if (!(create_args(instruction->args_of_func, params)))
		return (SYNTAX_ERROR);

    if (data->label_present == 1)
    {
    	label = data->label;
    	while (label)
		{
			if (!label->instruction)
				label->instruction = instruction;
			label = label->next;
		}
        data->label_present = 0;
    }
    push_back(data, instruction);
    return (0);
}



int create_args(t_args **args_of_func, char **params)
{
    int i;
	unsigned char type;

    i = 0;
    while (params[i])
    {
		if (!(args_of_func[i] = (t_args *)ft_memalloc(sizeof(t_args))) ||
			!(type = get_type(params[i])))
			return (0);

		args_of_func[i]->type = type;//todo совместить с предыдущей проверкой типа

		if (check_ending(params[i] + skip_word(params[i])))
			return (0);
		args_of_func[i]->str = params[i];
        i++;
    }
	return (1);
}
