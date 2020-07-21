/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 19:13:16 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/21 23:21:44 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <unistd.h>
# include "op.h"
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include "ft_printf/includes/ft_printf.h"
# include "libft/libft.h"

# define ERR_INVALID_CODE_SIZE	"ERROR: Invalid code size"

extern int errno;

typedef struct s_vm_field_memory
{
	unsigned char *field;
	t_op		*op_tab;
	bool		modulo;
}			t_vm_field_memory; 

typedef struct 			s_player
{
	t_header			player_header;
	int					ident;
	unsigned char		*code;
	// u_int64_t			last_live_cycle_number;
}						t_player;

typedef struct s_player_process
{
	u_int64_t	PC;
	u_int8_t		operation_code;
	// uint8_t		operation_args_type;
	u_int8_t	registers[REG_NUMBER*REG_SIZE];
	u_int64_t	cycles_to_wait;
	u_int64_t	live_counter;
	// u_int64_t	live_counter_valid;
	u_int64_t	last_live_cycle_number;
	bool		carry;
	u_int8_t	reg[3];
	u_int8_t	args[3];
	int64_t		arg_position;
	u_int64_t	ident;
	u_int64_t	parent;
	struct s_player_process *next;
	struct s_player_process *prev;
	bool		flag;
	
}				t_player_process;

typedef struct			s_player_list
{
	t_player					*player;
	int							position;
	struct s_player_list		*next;
	struct s_player_list		*prev;
}						t_player_list;

typedef struct s_game_process		/*Хранит*/
{
	u_int64_t	cycle_number;
	int64_t		cycle_to_die;
	t_player_list *begin_list;
	u_int64_t	dump_cycle;
	u_int64_t	d_cycle;
	bool		dump_flag;
	int			bytes_dump_per_line;
	u_int64_t	number_of_live_since_last_check;
	u_int64_t	checks_counter;
	t_op		*op_tab;
	bool 		aff;
	u_int64_t	process_numbers;
	bool		flag_a;
	u_int8_t	flag_v;
	t_player_process	*beginner;
	t_player_list		*last_live_player;
}				t_game_process;

// void (*operation[16])(t_game_process *game_process, t_player_process *player_process,
// 	t_player_list *player_list, t_vm_field_memory *vm_field_memory) =
// {
// 	op1
// };

// void (*operation[16])(t_game_process *game_process, t_player_process *player_process,
// 					  t_player_list *player_list, t_vm_field_memory *vm_field_memory) =
// {
// 		// op01(game_process, player_process, player_list, vm_field_memory),
// 		// op02(game_process, player_process, player_list, vm_field_memory),
// 		// op03(game_process, player_process, player_list, vm_field_memory),
// 		// op04(game_process, player_process, player_list, vm_field_memory),
// 		// op05(game_process, player_process, player_list, vm_field_memory),
// 		// op06(game_process, player_process, player_list, vm_field_memory),
// 		// op07(game_process, player_process, player_list, vm_field_memory),
// 		// op08(game_process, player_process, player_list, vm_field_memory),
// 		// op09(game_process, player_process, player_list, vm_field_memory),
// 		// op10(game_process, player_process, player_list, vm_field_memory),
// 		op11/*(game_process, player_process, player_list, vm_field_memory)*/,
// 		op12/*(game_process, player_process, player_list, vm_field_memory)*/,
// 		// op13(game_process, player_process, player_list, vm_field_memory),
// 		// op14(game_process, player_process, player_list, vm_field_memory),
// 		op15/*(game_process, player_process, player_list, vm_field_memory)*/,
// 		op16/*(game_process, player_process, player_list, vm_field_memory)*/

// };

void virtual_machine(t_game_process *game_process,
	t_player_list *player_list,  t_op *op_tab);
void 	parse_arguments(char **argv, t_game_process *game_process, t_player_list **player_list);
void 	memory_allocator_helper(char *str, char **buff);
size_t	ft_count_words(char const *s, char c);
void	op1(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory);
t_player_process *players_operations_executing(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory);
void operation_completer(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory);
bool	move_pc(t_op *op_tab, t_player_process *player_process,
	t_game_process *game_process, t_vm_field_memory *vm_field_memory);
t_player_process *create_processes(t_player_list *player_list,
	int divider, t_vm_field_memory *vm_field_memory, t_game_process *game_process);
void	arguments_memory_deleter(char **argv);
void	memory_deleter(t_player_list *player_list, t_vm_field_memory *vm_field_memory,
	t_game_process *game_process);
void	memory_error_cleaner(t_player_process *player_process);
int		ft_printf(char *format, ...);

#endif