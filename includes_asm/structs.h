/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/07/23 17:02:23 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_STRUCTS_H
# define COREWAR_STRUCTS_H

typedef struct s_label			t_label;
typedef struct s_instruction	t_instruction;

typedef	struct		s_op
{
	char			*name;
	int				func_num;
	int				arg_num;
	unsigned char	arg[3];
	int				arg_type_code;
	int				t_dir_size;
}					t_op;

struct				s_label
{
	char			*label_name;
	t_instruction	*instruction;
	t_label			*next;
};

typedef struct		s_args
{
	unsigned char	type;
	int				size;
	char			*str;
}					t_args;

struct				s_instruction
{
	int				position;
	char			function;
	t_op			*op;
	int				num_of_args;
	t_args			**args_of_func;
	t_instruction	*next;
	int				line;
};

typedef struct		s_struct
{
	char			*file_name;
	char			*name;
	char			*comment;
	int				code_length;
	t_instruction	*instruction;
	t_label			*label;
	int				label_present;
	int				line;
	char			*gnl_buf;
	int				file_size;
	char			*file_arr;
	char			*file_arr_start;
}					t_struct;

#endif
