
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


int check_type(char **params, t_op *op)
{
    char type;
    char *param;
    int i;

    i = 0;
    while (i < op->arg_num) {
        param = params[i] + skip_spaces(params[i]);
        type = get_type(param);
        if (!(type & op->arg[i]))
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

    if (trim_param[0] == '%')
    {
        if (ft_isdigit(trim_param[1]) || trim_param[1] == '-')
            return (T_DIR);

        if (trim_param[1] == ':')
            return (T_DIR);//todo remove T_LAB
    }

    if (trim_param[0] == ':')
        return (T_IND);//todo remove T_LAB
    return (0);//TODO проверить, может ли быть ошибка, если да, то какой ретюрн
}


void free_arr(char **arr)
{
    char *tmp;

    tmp = *arr;
    while (tmp != NULL)
    {
        free(tmp);
        tmp++;
    }
    free(arr);
}

int check_param(t_struct *data, char *str, t_op *op)// str2 already starts with word! not contains comments
{
	char **params;

	if (!(params = ft_strsplit(str, SEPARATOR_CHAR)))
	    return (MALLOC_FAIL);
	if (!(check_params_num(params, op->arg_num) && check_type(params, op)) )
	{
        free_arr(params);
        free(str);
        return (SYNTAX_ERROR);
    }
	else
	{
        free(str);
        return (create_instruction(op, params, data));
	}
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

    instruction->function = op->func_num;
    instruction->num_of_args = op->arg_num;//todo add to the new version
    create_args(instruction->args_of_func, params);

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


void create_args(t_args **args_of_func, char **params)
{
    int i;

    i = 0;
    while (params[i])
    {
        args_of_func[i] = (t_args *)ft_memalloc(sizeof(t_args));//TODO защитить маллок
        args_of_func[i]->type = get_type(params[i]);
        args_of_func[i]->str = params[i];
        i++;
    }
}

