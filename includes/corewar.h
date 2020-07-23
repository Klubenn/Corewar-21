/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 19:13:16 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/23 23:55:17 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <unistd.h>
# include "op.h"
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include "../ft_printf/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>

typedef struct					s_vm_field_memory
{
	unsigned char				*field;
	t_op						*op_tab;
	bool						modulo;
}								t_vm_field_memory;

typedef struct					s_player
{
	t_header					player_header;
	int							ident;
	unsigned char				*code;
}								t_player;

typedef struct					s_player_process
{
	u_int64_t					pc;
	u_int8_t					operation_code;
	u_int8_t					registers[REG_NUMBER * REG_SIZE];
	u_int64_t					cycles_to_wait;
	u_int64_t					live_counter;
	u_int64_t					last_live_cycle_number;
	bool						carry;
	u_int8_t					reg[3];
	u_int8_t					args[3];
	int64_t						arg_position;
	u_int64_t					ident;
	u_int64_t					parent;
	struct s_player_process		*next;
	struct s_player_process		*prev;
	bool						flag;
}								t_player_process;

typedef struct					s_player_list
{
	t_player					*player;
	int							position;
	struct s_player_list		*next;
	struct s_player_list		*prev;
}								t_player_list;

typedef struct					s_game_process
{
	char						**argv;
	int							*count;
	int							divider;
	bool						error_flag;
	u_int64_t					cycle_number;
	int64_t						cycle_to_die;
	t_player_list				*begin_list;
	u_int64_t					dump_cycle;
	u_int64_t					d_cycle;
	bool						dump_flag;
	int							bytes_dump_per_line;
	u_int64_t					number_of_live_since_last_check;
	u_int64_t					checks_counter;
	t_op						*op_tab;
	bool						aff;
	u_int64_t					process_numbers;
	bool						flag_a;
	u_int8_t					flag_v;
	t_player_process			*beginner;
	t_player_list				*last_live_player;
	t_player_list				*player_list;
}								t_game_process;

void							virtual_machine(t_game_process *game_process,
t_player_list *player_list, t_op *op_tab);
void							parse_arguments(t_game_process *game_process,
t_player_list **player_list);
void							memory_allocator_helper(char *str, char **buff);
size_t							ft_count_words(char const *s, char c);
t_player_process				*players_operations_executing(t_game_process
*game_process,
t_player_process *player_process, t_player_list *player_list,
t_vm_field_memory *vm_field_memory);
void							operation_completer(t_game_process
*game_process, t_player_process
*player_process, t_vm_field_memory *vm_field_memory);
bool							move_pc(t_op *op_tab,
t_player_process *player_process, t_game_process *game_process,
t_vm_field_memory *vm_field_memory);
t_player_process				*create_processes(t_player_list *player_list,
int divider, t_vm_field_memory *vm_field_memory,
t_game_process *game_process);
void							arguments_memory_deleter(char **argv);
void							memory_deleter(t_player_list *player_list,
t_vm_field_memory *vm_field_memory, t_game_process *game_process);
void							memory_error_cleaner(t_player_process
*player_process);
int								ft_printf(char *format, ...);
char							**memory_allocator_cmd_line_args(char **argv);
bool							parse_v(t_player_list *player_list_1,
t_player_list **player_list_2, t_game_process *game_process,
char **begin_buff_argv);
bool							parse_n(char ***argv,
t_player_list **player_list_2, t_game_process *game_process);
bool							parse_d(char **argv, int *count,
t_game_process *game_process);
bool							parse_dump(char **argv, int *count,
t_game_process *game_process);
int								check_position(t_player_list *player_list_1,
t_player_list *player_list_2);
int								check_position_help(t_player_list
*player_list_2, int len);
t_player_list					*player_stack_creator(t_player_list
*player_list_1, t_player_list *player_list_2,
t_game_process *game_process);
t_player_list					*stack_deleter(t_player_list *player_list,
int flag);
void							player_stack_creator_helper_3(t_player_list
**player_list_final,
int count, t_player_list **player_list,
t_game_process *game_process);
void							player_stack_creator_helper_4(t_player_list
**player_list_final,
int count, t_player_list **player_list,
t_game_process *game_process);
void							memory_is_not_enough(t_player_list
*player_list_1, t_player_list *player_list_2, t_game_process *game_process);
t_player_list					*stack_deleter(t_player_list *player_list,
int flag);
int								put_in_stack_of_players(int pos,
char *player_name, t_player_list **player_list);
int								check_arguments_errors(int fd,
char *player_name, t_player **player);
int								put_in_stack_of_players_helper(t_player_list
**player_list, t_player *player, int pos);
int								stack_member_initializer(t_player_list
**player_list, int pos, t_player *player,
t_player_list *player_list_prev);
int								players_reader_parse_champions(int fd,
t_player *player, char **argv);
int32_t							take_value_from_field(t_vm_field_memory
*vm_field_memory, t_player_process *player_process,
int size, u_int8_t type);
u_int32_t						bites_aggregator(t_vm_field_memory
*vm_field_memory, t_player_process *player_process,
int size, int32_t *i);
int32_t							make_number_positive(int64_t number);
int32_t							process_args(int i,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op16(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op15(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op14(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op13(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op12(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op11(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op10(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op9(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op6(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op7(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op8(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op7(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op6(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op5(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op4(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op3(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op2(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
void							op1(t_game_process *game_process,
t_player_process *player_process, t_vm_field_memory *vm_field_memory);
bool							validation_before_operation_complete(
t_game_process *game_process, t_player_process *player_process,
t_vm_field_memory *vm_field_memory);
void							memory_allocator_for_vm(t_player_list
*player_list, int divider, unsigned char *field);
int								vm_field_memory_initializer(
t_vm_field_memory **vm_field_memory, t_op *op_tab);
void							winner_definer(t_player_list
*player_list, t_game_process *game_process);
void							check_alives_1(t_game_process
*game_process, int *cycles_counter_between_checks,
t_player_process **player_process);
void							check_alives_1(t_game_process
*game_process, int *cycles_counter_between_checks,
t_player_process **player_process);
int								check_nulls_and_code_size(int count,
char *str, t_player *player, char **argv);
int								check_magic_header(char *str,
char **argv, t_player *player);
void							print_usage(void);
void							error_manager_for_parse_arguments(
t_player_list *player_list_1, t_player_list *player_list_2,
t_game_process *game_process, char **begin_buff_argv);
int								check_atoi_honest(char *argv);
void							print_operation_logs(t_player_process
*player_process, int32_t *arg_value, t_game_process *game_process);
void							put_value_to_register(u_int8_t
*regist, u_int32_t value);
void							op4_op5_helper(int32_t
*arg_value, t_player_process *player_process,
t_vm_field_memory *vm_field_memory);
void							deleter_and_live_counter(t_game_process
*game_process, u_int64_t *live_counter, t_player_process **player_process,
t_player_process **player_process_begin);
void							put_value_to_field(u_int32_t value,
t_vm_field_memory *vm_field_memory, u_int64_t pc);

#endif
