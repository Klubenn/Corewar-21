
#include <stdio.h>
#include <../libft/libft.h>
#include "../includes/op.h"
#include "../includes/asm.h"

void push_back(t_instruction **first_instruction, t_instruction *pInstruction1);

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
        if (!type != op->arg[i])
            return (0);
        i++;
    }
    return (1);
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


void free_arr(char **arr)
{
    char **tmp;

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
	int i;
	char type;

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

int create_instruction(t_op *op, char **params, t_struct *data)
{
    t_instruction *instruction;

    if (!(instruction = (t_instruction *)ft_memalloc(sizeof(t_instruction)))
        || !(instruction->args_of_func = (t_args	**)ft_memalloc(sizeof(t_args *) * 4)))
        return (MALLOC_FAIL);

    instruction->function = op->func_num;
    create_args(instruction->args_of_func, params);

    if (data->label_present == 1)
    {
        data->label->instruction = instruction;
        data->label_present = 0;
    }
    push_back(&(data->instruction), instruction);
    return (0);
}

void push_back(t_instruction **first_instruction, t_instruction *instruction)
{
    while (*first_instruction != NULL)
        (*first_instruction)++;
    *first_instruction = instruction;
}

t_args **create_args(t_args **args_of_func, char **params)
{
    int i;

    i = 0;
    while (params[i])
    {
        args_of_func[i] = (t_args *)ft_memalloc(sizeof(t_args));
        args_of_func[i]->type = get_type(params[i]);
        args_of_func[i]->str = params[i];
        i++;
    }
}



