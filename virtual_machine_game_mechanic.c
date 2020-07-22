/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_game_mechanics.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:06:36 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/22 18:11:46 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_memory(unsigned char *field, t_game_process *game_process)
{
	int counter;

	counter = 0;
	while (counter < MEM_SIZE)
	{
		if ((counter % game_process->bytes_dump_per_line) == 0)
		{
			if (counter != 0)
				ft_printf("\n");
			ft_printf("0x%04x : ", counter);
		}
		if (field[counter] / 16 > 0)
			ft_printf("%hhx ", field[counter]);
		else
			ft_printf("0%hhx ", field[counter]);
		counter++;
	}
	ft_printf("\n");
	exit(0);
}

void	play_corewar_while_cycle(t_game_process *game_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory,
	t_player_process *player_process)
{
	int	cycles_counter_between_checks;

	cycles_counter_between_checks = 0;
	while (player_process != NULL
		&& (game_process->dump_flag == false ||
			(game_process->dump_cycle > game_process->cycle_number
				|| game_process->d_cycle > game_process->cycle_number)))
	{
		cycles_counter_between_checks += 1;
		game_process->cycle_number += 1;
		if (game_process->flag_v & 2)
			ft_printf("It is now cycle %llu\n", game_process->cycle_number);
		player_process = players_operations_executing(game_process,
			player_process, player_list, vm_field_memory);
		if ((cycles_counter_between_checks == game_process->cycle_to_die)
				|| game_process->cycle_to_die <= 0)
		{
			check_alives_1(game_process, &cycles_counter_between_checks,
				&player_process);
		}
	}
}

void	play_corewar(t_game_process *game_process,
	t_player_list *player_list, int divider,
	t_vm_field_memory *vm_field_memory)
{
	t_player_process	*player_process;

	game_process->cycle_to_die = CYCLE_TO_DIE;
	game_process->cycle_number = 0;
	player_process = create_processes(player_list, divider,
		vm_field_memory, game_process);
	game_process->process_numbers = player_process->ident;
	play_corewar_while_cycle(game_process, player_list,
		vm_field_memory, player_process);
	if (game_process->dump_cycle == game_process->cycle_number ||
			game_process->d_cycle == game_process->cycle_number)
		print_memory(vm_field_memory->field, game_process);
	winner_definer(player_list, game_process);
	memory_deleter(player_list, vm_field_memory, game_process);
}

void	virtual_machine(t_game_process *game_process,
	t_player_list *player_list, t_op *op_tab)
{
	int					divider;
	t_player_list		*player_list_buff;
	t_vm_field_memory	*vm_field_memory;

	game_process->op_tab = op_tab;
	if (vm_field_memory_initializer(&vm_field_memory, op_tab))
	{
		memory_deleter(player_list, 0, game_process);
		exit(1);
	}
	player_list_buff = player_list;
	while (player_list_buff->next != 0)
		player_list_buff = player_list_buff->next;
	divider = player_list_buff->position;
	while (player_list_buff->prev != 0)
		player_list_buff = player_list_buff->prev;
	while (player_list_buff)
	{
		memory_allocator_for_vm(player_list_buff, divider,
			vm_field_memory->field);
		player_list_buff = player_list_buff->next;
	}
	play_corewar(game_process, player_list, divider,
		vm_field_memory);
}
