/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op11_op12_op15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 20:56:37 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 18:29:18 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	op11(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	int32_t	arg_value[3];

	vm_field_memory->modulo = false;
	player_process->arg_position = (player_process->pc + 2) % MEM_SIZE;
	arg_value[0] = process_args(0, player_process, vm_field_memory);
	if (player_process->args[1] == DIR_CODE)
		arg_value[1] = (int32_t)((int16_t)process_args(1,
			player_process, vm_field_memory));
	else
		arg_value[1] = process_args(1, player_process, vm_field_memory);
	if (player_process->args[2] == DIR_CODE)
		arg_value[2] = (int32_t)((int16_t)process_args(2,
			player_process, vm_field_memory));
	else
		arg_value[2] = process_args(2, player_process, vm_field_memory);
	if (player_process->arg_position >= 0)
	{
		put_value_to_field(arg_value[0], vm_field_memory,
			make_number_positive((int64_t)player_process->pc +
				(((int64_t)arg_value[1] + (int64_t)arg_value[2]) %
					(int64_t)IDX_MOD)));
		print_operation_logs(player_process, arg_value, game_process);
	}
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}

void	op12_15_new_initializer(t_player_process *new,
	t_game_process *game_process, t_player_process *player_process)
{
	new->prev->cycles_to_wait = 0;
	new->prev->next = new;
	new->prev->prev = NULL;
	game_process->beginner = new->prev;
	new->prev->ident = game_process->process_numbers + 1;
	new->prev->parent = player_process->ident;
	new->prev->live_counter = 0;
	new->prev->args[0] = 0;
	new->prev->args[1] = 0;
	new->prev->args[2] = 0;
	game_process->process_numbers += 1;
}

void	op12(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	t_player_process	*new;
	int64_t				bias;

	vm_field_memory->modulo = false;
	new = game_process->beginner;
	if (!(new->prev = (t_player_process *)
		ft_memalloc(sizeof(t_player_process))))
	{
		memory_error_cleaner(game_process->beginner);
		memory_deleter(game_process->begin_list, vm_field_memory, game_process);
		perror("Error");
		exit(1);
	}
	ft_memcpy(new->prev, player_process, sizeof(t_player_process));
	player_process->arg_position = (player_process->pc + 1) % MEM_SIZE;
	bias = (((int64_t)(int16_t)(take_value_from_field(vm_field_memory,
		player_process, 2, DIR_CODE))) % ((int64_t)IDX_MOD));
	new->prev->pc = (u_int64_t)make_number_positive(bias
		+ (int64_t)(player_process->pc));
	op12_15_new_initializer(new, game_process, player_process);
	print_operation_logs(new->prev, ((int32_t *)(&bias)), game_process);
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}

void	op15(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	t_player_process	*new;
	int64_t				bias;

	new = game_process->beginner;
	vm_field_memory->modulo = false;
	if (!(new->prev = (t_player_process *)
		ft_memalloc(sizeof(t_player_process))))
	{
		memory_error_cleaner(game_process->beginner);
		memory_deleter(game_process->begin_list, vm_field_memory, game_process);
		perror("Error");
		exit(1);
	}
	ft_memcpy(new->prev, player_process, sizeof(t_player_process));
	player_process->arg_position = (player_process->pc + 1) % MEM_SIZE;
	bias = ((int64_t)(int16_t)(take_value_from_field(vm_field_memory,
		player_process, 2, DIR_CODE)));
	new->prev->pc = (u_int64_t)make_number_positive(bias +
		(int64_t)(player_process->pc));
	op12_15_new_initializer(new, game_process, player_process);
	print_operation_logs(new->prev, ((int32_t *)(&bias)), game_process);
	move_pc(game_process->op_tab, player_process,
		game_process, vm_field_memory);
}
