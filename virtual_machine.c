/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:06:36 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/21 22:00:33 by gtapioca         ###   ########.fr       */
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
	int divider, t_vm_field_memory *vm_field_memory, t_game_process *game_process)
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
			
			if (!(begin = (t_player_process *)ft_memalloc(sizeof(t_player_process))))
			{
				memory_deleter(game_process->begin_list, vm_field_memory, game_process);
				perror("Error");
				exit(1);
			}
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
			game_process->beginner = player_process;
			player_process->cycles_to_wait = (vm_field_memory->op_tab)[(vm_field_memory->field)[player_process->PC]].cycles_before_complete;
			// printf("%llu %llu %llu\n", player_process->ident, player_process->PC, player_process->cycles_to_wait);
		}
		else
		{
			if (!(player_process->next = (t_player_process *)ft_memalloc(sizeof(t_player_process))))
			{
				memory_error_cleaner(game_process->beginner);
				memory_deleter(game_process->begin_list, vm_field_memory, game_process);
				perror("Error");
				exit(1);
			}
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
		if ((player_process->live_counter == 0 &&
				game_process->cycle_number - player_process->last_live_cycle_number >= game_process->cycle_to_die)
					|| game_process->cycle_to_die <= 0)
		{
			player_process_buff = player_process;
			if (game_process->beginner == player_process_buff)
				game_process->beginner = player_process->next;
			// if (player_process->live_counter != 0)
			live_counter = live_counter + player_process->live_counter;
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
			// if (player_process->live_counter > live_counter)
			// 	live_counter = player_process->live_counter;
			live_counter = live_counter + player_process->live_counter;
			player_process->live_counter = 0;
			player_process = player_process->next;
		}
	}
	if (live_counter >= NBR_LIVE)
	{
		// if (game_process->cycle_to_die > 0)
		// {
		game_process->cycle_to_die -= CYCLE_DELTA;
		if (game_process->flag_v & 2)
			printf("Cycle to die is now %d\n", (int32_t)game_process->cycle_to_die);
		// }
		game_process->checks_counter = 0;
	}
}

void winner_definer(t_player_list *player_list, t_game_process *game_process)
{
	if (game_process->last_live_player)
	{
		printf("Contestant %d, \"%s\", has won !\n",
			game_process->last_live_player->position,
				game_process->last_live_player->player->player_header.prog_name);
		return ;
	}
	while (player_list->next)
		player_list = player_list->next;
	printf("Contestant %d, \"%s\", has won !\n", player_list->position,
		player_list->player->player_header.prog_name);
}

void print_memory(unsigned char *field, t_game_process *game_process)
{
	int counter;

	counter = 0;
	while (counter < MEM_SIZE)
	{
		if ((counter % game_process->bytes_dump_per_line) == 0)
		{
			if (counter != 0) 
				printf("\n");
			printf("0x%04x : ", counter);	
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
	player_process = create_processes(player_list, divider, vm_field_memory, game_process);
	game_process->process_numbers = player_process->ident;
	while(player_process != NULL
			&& (game_process->dump_flag == false || (game_process->dump_cycle > game_process->cycle_number
				 || game_process->d_cycle > game_process->cycle_number)))
	{
		cycles_counter_between_checks += 1;
		game_process->cycle_number += 1;
		if (game_process->flag_v & (u_int8_t)2)
			printf("It is now cycle %llu\n", game_process->cycle_number);
		player_process = players_operations_executing(game_process,
			player_process, player_list, vm_field_memory);
		if ((cycles_counter_between_checks == game_process->cycle_to_die)
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
	if (game_process->dump_cycle == game_process->cycle_number ||
			game_process->d_cycle == game_process->cycle_number)
		print_memory(vm_field_memory->field, game_process);
	winner_definer(player_list, game_process);
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

int vm_field_memory_initializer(t_vm_field_memory **vm_field_memory,
	t_op *op_tab)
{
	if (!(*vm_field_memory =
		(t_vm_field_memory *)ft_memalloc(sizeof(t_vm_field_memory))))
	{
		perror("Error");
		return (1);
	}
	if (!((*vm_field_memory)->field =
		(unsigned char *)ft_memalloc(MEM_SIZE * sizeof(u_int8_t))))
	{
		free(*vm_field_memory);
		perror("Error");
		return (1);
	}
	(*vm_field_memory)->op_tab = op_tab;
	return (0);
}

void virtual_machine(t_game_process *game_process,
	t_player_list *player_list,  t_op *op_tab)
{
	int				counter;
	int				divider;
	t_player_list	*player_list_buff;
	t_vm_field_memory *vm_field_memory;

	game_process->op_tab = op_tab;
	if (vm_field_memory_initializer(&vm_field_memory, op_tab))
	{
		memory_deleter(player_list, 0, game_process);
		exit(1);
	}
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
	play_corewar(game_process, player_list, divider, vm_field_memory);
}