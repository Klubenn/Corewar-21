
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


int check_param(char *str, t_op *op)// str already starts with word!
{
	char **params;
	char *param;
	int i;
	char type;

	params = ft_strsplit(str, SEPARATOR_CHAR);
	if (!check_params_num(params, op->arg_num))
		error_managment();
	i = 0;
	while (i < op->arg_num)
	{
		param = &params[i][skip_spaces(params[i])];
		if (!check_type(param, i, op))
			error_managment();
		i++;
	}
}

int check_type(char **arr, int i, t_op *op)
{
	char type;

	type = get_type(arr[i]);
	if (type != op->arg[i])
		return (0);
	else
		return (1);
}


int check_params_num(char **params, int needed_num)
{
	int i;

	i = 0;
	while (params[i])
		i++;
	return (i == needed_num) ? 1 : 0;
}