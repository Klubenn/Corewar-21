
#include <stdio.h>
#include <libft.h>
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
	op = ft_strsub(str, 0, instr_len);// TODO обработать ошибки strsub

	while (i < 16)
	{
		if (ft_strcmp(op, op_tab[i].func_num) == 0)
			return (&(op_tab[i]));
		i++;
	}
	return (NULL);
}

int skipper(int if_chars, char* str)
{
    int i;

    i = 0;
    if (if_chars)
    {
        while (!ft_isspace(str[i]) && str[i] != '\0')
			i++;
    }
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int check_param(char *str, t_op *op)
{
	char **params;
	char *param;
	int i;

	params = ft_strsplit(str, SEPARATOR_CHAR);
	if (!check_params_num(params, op->arg_num))
		error_managment();
	i = 0;
	while (i < op->arg_num)
	{
		param = ft_strtrim(params[i]);
		if (!check_type(param))
			error_managment();
		i++;
	}
}

int check_params_num(char **params, int needed_num)
{
	int i;

	i = 0;
	while (params[i])
		i++;
	return (i == needed_num) ? 1 : 0;
}

