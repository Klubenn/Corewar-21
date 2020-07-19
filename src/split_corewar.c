#include "op.h"

int		calculate_separators(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == SEPARATOR_CHAR)
			i++;
		str++;
	}
	return (i);
}

int word_length(char *str)
{
	int i;

	i = 0;
	str += skip_spaces(str);
	while (str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != SEPARATOR_CHAR)
		i++;
	return (i);
}

int write_word(char **str, int length, char *split)
{
	int i;

	i = 0;
	*str += skip_spaces(*str);
	while (i < length)
	{
		split[i] = (*str)[i];
		i++;
	}
	*str +=length;
	*str += skip_spaces(*str);
	if (**str == SEPARATOR_CHAR)
		(*str)++;
	else if (**str != '\0')
		return (-1);
	return (0);
}

char **split_corewar(char *str)
{
	int params;
	char **split;
	int i;
	int length;

	params = calculate_separators(str) + 1;
	i = 0;
	if (!(split = (char **)ft_memalloc(sizeof(char *) * params + 1)))
		return (NULL);
	while (i < params)
	{
		length = word_length(str);
		if (!(split[i] = (char *)ft_memalloc(sizeof(char) * (length + 1)))
			|| write_word(&str, length, split[i]))
		{
			free_arr(split);
			return (NULL);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}
