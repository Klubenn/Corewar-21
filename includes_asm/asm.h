/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/24 23:09:17 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_ASM_H
# define COREWAR_ASM_H

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/header_pf.h"
# include "op.h"
# include "structs.h"

enum	e_err_message
{
	USAGE = 1,
	FILE_NAME,
	END_INPUT,
	NO_FILE,
	TOP_FILE,
	DOT_START,
	MALLOC_FAIL,
	LONG_NAME,
	LONG_COMM,
	QUOTES_BEGIN,
	QUOTES_END,
	SYNTAX_ERROR,
	WRONG_REG,
	WRONG_NUM,
	DUPL_LABEL,
	NOT_EXIST,
	MULTIPLE_NAME,
	MULTIPLE_COMMENT,
	LABEL_NOT_FOUND,
	INCORRECT_ARGUMENT,
	CANT_CREATE_FILE,
};

void	bin_exec_champ(t_struct *data);
void	write_backwards(t_struct *data, void *source, int size);
void	instructions_position(t_struct *data);
void	check_labels(t_struct *data);
void	to_bytecode(t_struct *data);
void	error_management(int err, t_struct *data, int line_num);
int		check_other_strings(char *str, t_struct *data);
int		check_label(t_struct *data, char *str);
int		create_instruction(t_op *op, char **params, t_struct *data);
int		create_args(t_args **args_of_func, char **params);
int		check_params(char **params, t_op *op);
char	*trim_start(char *str);
t_op	*check_op(char *str);
int		skip_spaces(char *str);
int		skip_word(char *str);
int		check_param(t_struct *data, char *str, t_op *op);
char	get_type(char *param);
int		check_ending(char *str);
void	free_data(t_struct *data);
int		gnl(int fd, char **line, char **gnl_buf);
char	**split_corewar(char *str);
void	free_arr(char **arr);
void	write_to_array(char *ptr, char c);
int		corewar_atoi(char *arg, void *numptr, int size, int digits);
void	arguments_code(t_struct *data, t_instruction *instruction);
char	*cut_string(char *str);
void	free_strings(char *str1, char *str2, char *str3, char *str4);
void	process_name_and_comment(char *str, t_struct *data, int fd);
int		argument_size(t_instruction *instruction);
void	bin_champ_name(t_struct *data);
void	bin_comment(t_struct *data);
void	process_string(char *str, t_struct *data, int fd);
void	bin_exec_code_size(t_struct *data);
void	bin_null(t_struct *data);
void	bin_magic(t_struct *data);

#endif
