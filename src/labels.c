# include "asm.h"

int		find_label(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			return (i);
		if (!ft_strchr(LABEL_CHARS, str[i]))
			return (0);
		i++;
	}
	return (0);
}

int		check_label(t_struct *data, char *str)
{
	int len;
	t_label *lab;

	if ((len = find_label(str)))
	{
		data->label_present = 1;
		if (!data->label)
		{
			if (!(data->label = (t_label *)ft_memalloc(sizeof(t_label))))
				return (-1);//TODO check for -1 return and give MALLOC_FAIL return to it
			data->label->label_name = ft_strndup(str, len);
			return (len + 1);
		}
		lab = data->label;
		while(lab->next)
			lab = lab->next;
		if (!(lab->next = (t_label *)ft_memalloc(sizeof(t_label))))
			return (-1);
		lab->next->label_name = ft_strndup(str, len);
		return (len + 1);
	}
	return (0);
}