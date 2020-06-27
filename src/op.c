
#include <stdio.h>
#include <../libft/libft.h>
#include "../includes/op.h"
#include "../includes/asm.h"



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
