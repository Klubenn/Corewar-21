/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   asm.c											  :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: etuffleb <etuffleb@student.42.fr>		  +#+  +:+	   +#+	          */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2019/11/28 18:07:51 by etuffleb		  #+#	#+#			      */
/*   Updated: 2020/03/15 20:57:39 by etuffleb		 ###   ########.fr	      */
/*																			  */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../includes/op.h"
#include "../includes/asm.h"

void	print_error_message(enum err_message num)
{
	static char *ch[] = {
			NULL,
			"usage: ./asm file_name\n",											//USAGE
			"Wrong file name. Should have an \".s\" extension.\n",				//FILE_NAME
			"Syntax error - unexpected end of input. Missing end of line.\n",	//END_INPUT
			"Can't open the file.\n",											//NO_FILE
			"Name and comment should be at the top of file.\n",					//TOP_FILE
			"Only a name or a comment can begin with a \'.\'\n",				//DOT_START
			"Memory allocation failed.\n",										//MALLOC_FAIL
			"Champion name is too long.\n",										//LONG_NAME
			"Champion comment is too long.\n",									//LONG_COMM
			"Champion name must be before comment.\n",							//COMM_BEFORE_NAME
			"Name and comment should start with the quotes.\n",					//QUOTES_BEGIN
			"Name and comment should end with the quotes.\n",					//QUOTES_END
			"Syntax error.\n",													//SYNTAX_ERROR
	};
	ft_putstr_fd(ch[num], 2);
}

char 		*trim_start(char *str)
{
	if (str)
	{
		while(*str == ' ' || *str == '\t')
			str++;
	}
	return (str);
}

int		check_ending(char *str)
{
	if (str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (!*str || *str == COMMENT_CHAR)
			return (0);
	}
	return (1);
}

void	free_data(t_struct *data)
{
	free(data);//TODO write more later
}

void	error_management(int err, t_struct *data)
{
	if (err)
		print_error_message(err);
	if (data)
		free_data(data);
	exit(1);
}

char *remove_comment_from_string(char *str)
{
	char *tmp;

	if (!(tmp = ft_strchr(str, COMMENT_CHAR)))
		return (ft_strdup(str));
	return (ft_strndup(str, tmp - str));
}

int	check_other_strings(char *str, t_struct *data)
{
	t_op *op;
	int if_label;
	char *str2;

	if ((if_label = check_label(data, str)) < 0)
		return (MALLOC_FAIL);
	str = trim_start(str + if_label);
	if (!(op = check_op(str)))
		return (SYNTAX_ERROR);
	str = trim_start(str + skip_word(str));
	if (!(str2 = remove_comment_from_string(str)))
		return (MALLOC_FAIL);
	return (check_param(data, str2, op));
}

void	free_strings(char *str1, char *str2, char *str3, char *str4)
{
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

int 	finish_reading(char **string, char *tmp2, char *small, char *big)
{
	char *tmp1;

	if (big)
		tmp1 = big;
	else
		tmp1 = ft_strdup("\n");
	if (!check_ending(tmp2 + 1))
	{
		big = ft_strndup(small, tmp2 + 1 - small);
		*string = ft_strjoin(tmp1, big);
		free_strings(small, tmp1, big, NULL);
		return (0);
	}
	free_strings(small, tmp1, NULL, NULL);
	return (SYNTAX_ERROR);
}

int		continue_reading(int fd, char **string)
{
	char *small;
	char *big;
	char *tmp1;
	char *tmp2;
	tmp1 = ft_strdup("\n");
	big = NULL;
	while(get_next_line(fd, &small) > 0)
	{
		if ((tmp2 = ft_strchr(small, '"')))
			return (finish_reading(string, tmp2, small, big));
		tmp2 = ft_strjoin(tmp1, small);
		big = ft_strjoin(tmp2, "\n");
		free_strings(tmp1, tmp2, small, NULL);
		tmp1 = big;
		if (ft_strlen(big) > COMMENT_LENGTH)
			break ;
	}
	free(tmp1);
	return(QUOTES_END);
}

int 	write_name_comment(char *substring, t_struct *data, size_t len)
{
	if (len == PROG_NAME_LENGTH)
	{
		if (ft_strlen(substring) > len)
		{
			free(substring);
			return (LONG_NAME);
		}
		data->name = substring;
	}
	else
	{
		if (ft_strlen(substring) > len)
		{
			free(substring);
			return (LONG_COMM);
		}
		data->comment = substring;
	}
	return (0);
}

int		extract_name_comment(char *str, t_struct *data, int fd, int len)
{
	char *substring;
	char *add_string;
	int i;

	while (*str == ' ' || *str == '\t')
		str++;
	if (!*str || *str != '"')
		return(QUOTES_BEGIN);
	i = 1;
	while (str[i] && str[i] != '"')
		i++;
	if (!str[i])
	{
		if ((i = continue_reading(fd, &add_string)))
			return (i);
		substring = ft_strjoin(str, add_string);
		free(add_string);
	}
	else if (!check_ending(str + i + 1))
		substring = ft_strndup(str, i + 1);
	else
		return (SYNTAX_ERROR);
	return (write_name_comment(substring, data, len));
}

void	process_name_and_comment(char *str, t_struct *data, int fd)
{
	int err;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == COMMENT_CHAR || !*str)
		return ;
	if (ft_strnequ(str, NAME_CMD_STRING, 5))
		err = extract_name_comment(str + 5, data, fd, PROG_NAME_LENGTH);
	else if (ft_strnequ(str, COMMENT_CMD_STRING, 8))
		err = (data->name ? extract_name_comment(str + 8, data, fd, COMMENT_LENGTH) : COMM_BEFORE_NAME);
	else
		err = (TOP_FILE);
	if (err)
		error_management(err, data);
}

void		process_string(char *str, t_struct *data, int fd)
{
	int		error;
	char	*str_trim;

	str_trim = trim_start(str);
	if (!*str_trim || *str_trim == COMMENT_CHAR)
		return ;
	if (*str_trim == '.')
		error = DOT_START;
	else
		error = check_other_strings(str_trim, data);
	if (error)
	{
		free(str);
		close (fd);
		error_management(error, data);
	}
}

t_struct	*is_valid_file(char *file_name, char *new_file)
{
	int			fd;
	int 		flag;
	char		*str;
	t_struct	*data;

	flag = 1;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		error_management(NO_FILE, NULL);
	if (!(data = (t_struct *)ft_memalloc(sizeof(t_struct))))
		error_management(MALLOC_FAIL, NULL);
	data->file_name = new_file;
	while (get_next_line(fd, &str) > 0)
	{
		if (!data->name || !data->comment)
			process_name_and_comment(str, data, fd);
		else
			process_string(str, data, fd);
		flag = check_ending(str);
		free(str);
	}
	close(fd);
	if (flag)
		error_management(END_INPUT, data);
	return (data);
}

char *change_extension(char *file_name)
{
	int i;
	char	*new_file;

	if (!file_name)
		return (NULL);
	i = ft_strlen(file_name);
	while (i >= 0)
	{
		if (file_name[i] == '.')
		{
			if (i == 0 || ft_strcmp(file_name + i, ".s"))
				return (NULL);
			else
			{
				new_file = (char *)ft_memalloc((i + 5) * (sizeof(char)));
				ft_strncpy(new_file, file_name, i);
				ft_strncpy(&(new_file[i]), ".cor", 4);
				return (new_file);
			}
		}
		i--;
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	int			i;
	t_struct	*data;
	char		*new_file;

	i = 1;
	if (ac < 2)
		error_management(USAGE, NULL);
	while (i < ac)
	{
		if (!(new_file = change_extension(av[i])))//записать название файла в структуру
			error_management(FILE_NAME, NULL);
		else
		{
			data = is_valid_file(av[i], new_file);
			instructions_position(data);
			check_labels(data);
			to_bytecode(data);
			printf("file %s was successfully created\n", new_file);//TODO change to ft_printf
			free_data(data);
		}
		i++;
	}
	return (0);
}
