/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:06:36 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/18 20:47:26 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include "corewar.h"
#include "libft/libft.h"
#include <fcntl.h>
#include "op.h"

t_player_process *create_processes(t_player_list *player_list,
	int divider, t_vm_field_memory *vm_field_memory)
{
	t_player_process	*begin;
	t_player_process	*player_process;
	int					counter;

	while (player_list->next)
		player_list = player_list->next;
	while (player_list)
	{
		counter = REG_SIZE - 1;
		if (player_list->next == 0)
		{
			begin = (t_player_process *)ft_memalloc(sizeof(t_player_process));
			while(counter > 0)
			{
				begin->registers[counter] = (unsigned char)(255);
				counter--;
			}
			// counter = REG_SIZE;
			// while (counter < (REG_NUMBER * REG_SIZE))
			// {
			// 	begin->registers[counter] = 0;
			// 	counter++;
			// }
			begin->registers[counter] = (unsigned char)(-1 * (player_list->position));
			player_process = begin;
			player_process->next = 0;
			player_process->prev = 0;
			player_process->ident = (u_int64_t)(*((int *)(&(player_process->registers[0]))))*(-1);
			player_process->carry = false;
			player_process->PC = (MEM_SIZE / divider) * (player_list->position - 1);
			player_process->operation_code = vm_field_memory->field[player_process->PC];
			player_process->cycles_to_wait = (vm_field_memory->op_tab)[(vm_field_memory->field)[player_process->PC]].cycles_before_complete;
			// printf("%llu %llu %llu\n", player_process->ident, player_process->PC, player_process->cycles_to_wait);
		}
		else
		{
			player_process->next = (t_player_process *)ft_memalloc(sizeof(t_player_process));
			player_process->next->prev = player_process;
			player_process = player_process->next;
			player_process->next = 0;
			while(counter > 0)
			{
				player_process->registers[counter] = (unsigned char)(255);
				counter--;
			}
			// counter = REG_SIZE;
			// while (counter < (REG_NUMBER * REG_SIZE))
			// {
			// 	begin->registers[counter] = 0;
			// 	counter++;
			// }
			player_process->registers[counter] = (unsigned char)(-1 * (player_list->position));
			player_process->PC = (MEM_SIZE / divider) * (player_list->position - 1);
			player_process->carry = false;
			player_process->ident = (u_int64_t)(*((int *)(&(player_process->registers[0]))))*(-1);
			player_process->operation_code = vm_field_memory->field[player_process->PC];
			player_process->cycles_to_wait = (vm_field_memory->op_tab)[(vm_field_memory->field)[player_process->PC]].cycles_before_complete;
			// printf("%llu %llu %llu\n", player_process->ident, player_process->PC, player_process->cycles_to_wait);
		}
		player_list = player_list->prev;
	}
	return (begin);
}

void delete_process(t_player_process *player_process,
	t_player_process **player_process_begin)
{
	if (player_process->prev != 0
		&& player_process->next != 0)
	{
		player_process->prev->next = player_process->next;
		player_process->next->prev = player_process->prev;
		free(player_process);
	}
	else if (player_process->prev != 0
		&& player_process->next == 0)
	{
		player_process->prev->next = 0;
		free(player_process);
	}
	else if (player_process->prev == 0
		&& player_process->next != 0)
	{
		player_process->next->prev = 0;
		*player_process_begin = player_process->next;
		free(player_process);
	}
	else if (player_process->prev == 0
		&& player_process->next == 0)
	{
		*player_process_begin = 0;
		free(player_process);
	}
}

void check_alives(t_game_process *game_process,
	t_player_process	**player_process_begin)
{
	u_int64_t			live_counter;
	t_player_process	*player_process;
	t_player_process	*player_process_buff;

	live_counter = 0;
	player_process = *player_process_begin;
	while(player_process)
	{
		if (player_process->live_counter == 0 || game_process->cycle_to_die <= 0)
		{
			player_process_buff = player_process;
			player_process = player_process->next;
			if (game_process->flag_v & 8)
				printf("Process %llu hasn't lived for %llu cycles (CTD %d)\n",
					player_process_buff->ident,
						game_process->cycle_number -
							player_process_buff->last_live_cycle_number,
								(int32_t)game_process->cycle_to_die);
			delete_process(player_process_buff, player_process_begin);
		}
		else
		{
			live_counter = live_counter + player_process->live_counter;
			player_process->live_counter = 0;
			player_process = player_process->next;
		}
	}
	if (live_counter >= NBR_LIVE)
	{
		if (game_process->cycle_to_die > 0)
		{
			game_process->cycle_to_die -= CYCLE_DELTA;
			if (game_process->flag_v & 2)
				printf("Cycle to die is now %d\n", (int32_t)game_process->cycle_to_die);
		}
		game_process->checks_counter = 0;
	}
}

void winner_definer(t_player_list *player_list)
{
	u_int64_t	last_live_cycle_number;
	int			winner_number;
	char		*winner_name;

	while (player_list->next)
		player_list = player_list->next;
	last_live_cycle_number = player_list->player->last_live_cycle_number;
	winner_number = player_list->position;
	winner_name = player_list->player->player_header.prog_name;
	while(player_list)
	{
		if (player_list->player->last_live_cycle_number > last_live_cycle_number)
		{
			last_live_cycle_number = player_list->player->last_live_cycle_number;
			winner_name = player_list->player->player_header.prog_name;
			winner_number = player_list->position;
		}
		player_list = player_list->prev;
	}
	printf("Player %d (%s) won\n", winner_number, winner_name);
}

void print_memory(unsigned char *field)
{
	int counter;

	counter = 0;
	while (counter < MEM_SIZE)
	{
		if (counter % 32 == 0)
		{
			if (counter != 0)
			{
				printf("\n");
				printf("%#.4x : ", counter);
			}
			else
				printf("000000 : ");	
		}
		if (field[counter] / 16 > 0)
			printf("%hhx ", field[counter]);
		else
			printf("0%hhx ", field[counter]);
		counter++;
	}
	printf("\n");
	exit(0);
}

void play_corewar(t_game_process *game_process, t_player_list *player_list, int divider,
	t_vm_field_memory *vm_field_memory)
{
	uint64_t			checks_counter;
	t_player_process	*player_process;
	int	cycles_counter_between_checks;

	cycles_counter_between_checks = 0;
	checks_counter = 0;
	game_process->cycle_to_die = CYCLE_TO_DIE;
	game_process->cycle_number = 0;
	player_process = create_processes(player_list, divider, vm_field_memory);
	game_process->process_numbers = player_process->ident;
	// printf("%llu\n", game_process->process_numbers);
	while(/* game_process->cycle_to_die > 0 && */player_process != NULL
			&& (game_process->dump_cycle == 0 || (game_process->dump_cycle > game_process->cycle_number)))
	{
		// if (cycles_counter_between_checks == game_process->cycle_to_die)
		// {
		// 	check_alives(game_process, &player_process);
		// 	game_process->checks_counter += 1;
		// 	cycles_counter_between_checks = 0;
		// 	if (game_process->checks_counter == MAX_CHECKS)
		// 	{
		// 		game_process->cycle_to_die -= CYCLE_DELTA;
		// 		game_process->checks_counter = 0;
		// 	}
		// }
		// else
		// {
		cycles_counter_between_checks += 1;
		game_process->cycle_number += 1;
		if (game_process->flag_v & (u_int8_t)2)
			printf("It is now cycle %llu\n", game_process->cycle_number);
		player_process = players_operations_executing(game_process,
			player_process, player_list, vm_field_memory);
		// cycles_counter_between_checks += 1;
		// }
		// game_process->cycle_number += 1;
		// if (game_process->flag_v & (u_int8_t)2)
		// 	printf("It is now cycle %llu\n", game_process->cycle_number);
		if ((cycles_counter_between_checks == game_process->cycle_to_die/* && game_process->cycle_to_die > 0*/)
				|| game_process->cycle_to_die <= 0)
		{
			game_process->checks_counter += 1;
			check_alives(game_process, &player_process);
			cycles_counter_between_checks = 0;
			if (game_process->checks_counter == MAX_CHECKS)
			{
				if (game_process->cycle_to_die > 0)
				{
					game_process->cycle_to_die -= CYCLE_DELTA;
					if (game_process->flag_v & 2)
						printf("Cycle to die is now %d\n", (int32_t)game_process->cycle_to_die);
				}
				game_process->checks_counter = 0;
			}
		}
	}
	if (game_process->dump_cycle == game_process->cycle_number)
		print_memory(vm_field_memory->field);
	// else
	// {
	// printf("\n\n%llu %llu\n", game_process->cycle_number, game_process->checks_counter);
	winner_definer(player_list);
	// }
	memory_deleter(player_list, vm_field_memory, game_process);
}

void memory_allocator_for_vm(t_player_list *player_list, int divider, unsigned char *field)
{
	int upper_boundary;
	int lower_boundary;
	int counter;

	counter = 0;
	upper_boundary = (MEM_SIZE / divider) * player_list->position;
	lower_boundary = (MEM_SIZE / divider) * (player_list->position - 1);
	while (lower_boundary < upper_boundary)
	{
		if (counter < player_list->player->player_header.prog_size)
			field[lower_boundary] = player_list->player->code[counter];
		else
			field[lower_boundary] = 0;
		counter++;
		lower_boundary++;
	}
}

void virtual_machine_creator(t_game_process *game_process,
	t_player_list *player_list,  t_op *op_tab)
{
	int				counter;
	int				divider;
	t_player_list	*player_list_buff;
	t_vm_field_memory *vm_field_memory;

	game_process->op_tab = op_tab;
	vm_field_memory = (t_vm_field_memory *)ft_memalloc(sizeof(t_vm_field_memory));
	vm_field_memory->field = (unsigned char *)ft_memalloc(MEM_SIZE);
	vm_field_memory->op_tab = op_tab;
	player_list_buff = player_list;
	while(player_list_buff->next != 0)
		player_list_buff = player_list_buff->next;
	divider = player_list_buff->position;
	while(player_list_buff->prev != 0)
		player_list_buff = player_list_buff->prev;
	while(player_list_buff)
	{
		memory_allocator_for_vm(player_list_buff, divider, vm_field_memory->field);
		player_list_buff = player_list_buff->next;
	}
	// print_memory(vm_field_memory->field);
	play_corewar(game_process, player_list, divider, vm_field_memory);
}

// void operation_log_printer(t_player_process *player_process, int32_t *arg_value, )
// {
	
// }