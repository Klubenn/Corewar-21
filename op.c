/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 19:43:05 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/21 23:24:10 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>
#include "op.h"
#include <stdio.h>

int pui = 5;

t_op    op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 0, 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 1, 4},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 0, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 0, 1, 2},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 2},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 0, 2},
	{"aff", 1, {T_REG}, 16, 2, "aff", 0, 1, 4}
};

char **memory_allocator(char **argv)
{
	int counter;
	int i;
	char **buff;

	i = 0;
	counter = 0;
	while (argv[i] != 0)
	{
		counter += ft_count_words(argv[i], ' ');
		i++;
	}
	if (!(buff = (char **)malloc(sizeof(char *)*(counter + 1))))
	{
		perror("Error");
		exit(1);
	}
	i = 0;
	while (i < counter)
	{
		buff[i] = 0;
		i++;
	}
	buff[counter] = 0;
	i = 0;
	while(argv[i] != 0)
	{
		memory_allocator_helper(argv[i], buff);
		i++;
	}
	return (buff);
}

void arguments_memory_deleter(char **argv)
{
	char **begin;

	begin = argv;
	while (*argv)
	{
		free(*argv);
		argv++;
	}
	free(*argv);
	free(begin);
}

void print_intro(t_player_list *player_list)
{
	ft_printf("Introducing contestants...\n");
	while(player_list != 0)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			player_list->position,
			player_list->player->player_header.prog_size,
			player_list->player->player_header.prog_name,
			player_list->player->player_header.comment);
		player_list = player_list->next;
	}
}

void game_process_initializer(t_game_process *game_process)
{
	game_process->cycle_to_die = CYCLE_TO_DIE;
	game_process->cycle_number = 0;
	game_process->dump_cycle = 0;
	game_process->dump_cycle = 0;
	game_process->number_of_live_since_last_check = 0;
	game_process->checks_counter = 0;
	game_process->last_live_player = 0;	
	game_process->begin_list = 0;
}

int main(int argc, char **argv)
{
	t_game_process *game_process;
	t_player_list	*player_list_1;
	t_player_list	*player_list;
	char **split_argv;

	argv++;
	split_argv = memory_allocator(argv);
	player_list = NULL;
	if (!(game_process = (t_game_process *)ft_memalloc(sizeof(t_game_process))))
	{
		arguments_memory_deleter(split_argv);
		perror("Error");
		exit(1);
	}
	parse_arguments(split_argv, game_process, &player_list);
	player_list_1 = player_list;
	// arguments_memory_deleter(split_argv);
	print_intro(player_list);
	game_process_initializer(game_process);
	virtual_machine(game_process, player_list, op_tab);
	// free(game_process);
	return(0);
}