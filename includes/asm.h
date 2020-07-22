#ifndef COREWAR_ASM_H
#define COREWAR_ASM_H

#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include "../libft/libft.h"
#include "header_pf.h"
//#include <zconf.h>
#include "op.h"

typedef struct		s_label t_label;
typedef struct		s_instruction t_instruction;

enum err_message
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
};


typedef	struct		s_op
{
	char			*name;
	int 			func_num;
	int 			arg_num;
	unsigned char	arg[3];
	int 			arg_type_code;
	int 			t_dir_size;
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
	int 			size;
	char			*str;
}					t_args;

struct 				s_instruction
{
	int 			position;
	char			function;
	t_op 			*op;
    int			    num_of_args;
	t_args			**args_of_func;
	t_instruction	*next;
	int 			line;
	char 			*str;
};

typedef struct		s_struct
{
	char			*file_name;
	char			*name;
	char			*comment;
	int 			code_length;
	t_instruction	*instruction;
	t_label			*label;
	int 			label_present;
	int 			line;
	char 			*gnl_buf;
	int 			file_size;
	char 			*file_arr;
	char 			*file_arr_start;
}					t_struct;

void	print_file(char *new_file);
void	bin_exec_champ(t_struct *data);
void	write_backwards(t_struct *data, void *source, int size);
void	instructions_position(t_struct *data);
void	check_labels(t_struct *data);
void    to_bytecode(t_struct *data);
void	error_management(int err, t_struct *data, int line_num);
int		check_other_strings(char *str, t_struct *data);
int		check_label(t_struct *data, char *str);
int     create_instruction(t_op *op, char **params, t_struct *data);
int		create_args(t_args **args_of_func, char **params);
int     check_params(char **params, t_op *op);
char	*trim_start(char *str);
t_op	*check_op(char *str);
int 	skip_spaces(char* str);
int 	skip_word(char* str);
int 	check_param(t_struct *data, char *str, t_op *op);
char    get_type(char *param);
int		check_ending(char *str);
void	free_data(t_struct *data);
int		gnl(int fd, char **line, char **gnl_buf);
char	**split_corewar(char *str);
void	free_arr(char **arr);
void	write_to_array(char *ptr, char c);


#endif //COREWAR_ASM_H
