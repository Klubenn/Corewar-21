/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_executing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:14:34 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/13 13:54:46 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include "corewar.h"
#include "libft/libft.h"
#include <fcntl.h>
#include "op.h"

// void	op1(t_game_process *game_process, t_player_process *player_process,
// 	t_player_list *player_list, t_vm_field_memory *vm_field_memory)
// {
	
// }

// void (*operation[16])(t_game_process *game_process, t_player_process *player_process,
// 	t_player_list *player_list, t_vm_field_memory *vm_field_memory) =
// {
// 	op1
// };

bool	move_pc(t_op *op_tab, t_player_process *player_process)
{
	u_int8_t	op_code;
	int counter;

	counter = 0;
	op_code = player_process->operation_code;
	if (op_tab[op_code].have_a_code_type_code == 0)
	{
		if (op_tab[op_code].arg_types[0] == T_REG)
		{
			player_process->PC = (player_process->PC + 1) % MEM_SIZE;
		}
		else if (op_tab[op_code].arg_types[0] == T_IND)
		{
			player_process->PC = (player_process->PC + IND_SIZE) % MEM_SIZE;
		}
		else if (op_tab[op_code].arg_types[0] == T_DIR)
		{
			player_process->PC = (player_process->PC + op_tab[op_code].dir_size) % MEM_SIZE;
		}
		player_process->PC = (player_process->PC + 1) % MEM_SIZE;
		return(false);
	}
	while (counter < 3)
	{
		if (player_process->args[counter] == REG_CODE)
		{
			player_process->PC = (player_process->PC + 1) % MEM_SIZE;
		}
		else if (player_process->args[counter] == IND_CODE)
		{
			player_process->PC = (player_process->PC + IND_SIZE) % MEM_SIZE;
		}
		else if (player_process->args[counter] == DIR_CODE)
		{
			player_process->PC = (player_process->PC + op_tab[op_code].dir_size) % MEM_SIZE;
		}
		counter++;
	}
	if (player_process->PC == MEM_SIZE - 1)
		player_process->PC = 1;
	else
		player_process->PC += 2;
	return (false);
}

bool	validation_before_operation_complete(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int8_t	args_type_code;
	u_int8_t	counter;
	u_int8_t	comparator;

	counter = 0;
	if (game_process->op_tab[player_process->operation_code].have_a_code_type_code == 0)
		return (true);
		// return (move_pc(game_process->op_tab, player_process));
	// 	if (game_process->op_tab[player_process->operation_code].arg_types[0] == T_REG)
	// 	{
	// 		player_process->PC = (player_process->PC + 1) % MEM_SIZE;
	// 	}
	// 	else if (game_process->op_tab[player_process->operation_code].arg_types[0] == T_IND)
	// 	{
	// 		player_process->PC = (player_process->PC + IND_SIZE) % MEM_SIZE;
	// 	}
	// 	else if (game_process->op_tab[player_process->operation_code].arg_types[0] == T_DIR)
	// 	{
	// 		player_process->PC = (player_process->PC + game_process->op_tab[player_process->operation_code].dir_size) % MEM_SIZE;
	// 	}
	// 	player_process->PC = (player_process->PC + 1) % MEM_SIZE;
	// 	return(true);
	// }
	// if (player_process->PC == MEM_SIZE - 1)
	// 	args_type_code = (vm_field_memory->field)[0];
	// else
	args_type_code = (vm_field_memory->field)[(player_process->PC + 1) % MEM_SIZE];
	player_process->args[0] = (args_type_code & 192) >> 6;
	player_process->args[1] = (args_type_code & 48) >> 4;
	player_process->args[2] = (args_type_code & 12) >> 2;
	while (counter < 3)
	{
		comparator = (game_process->op_tab)[player_process->operation_code].arg_types[counter];
		if (player_process->args[counter] == REG_CODE && !(comparator & T_REG))
			return (move_pc(game_process->op_tab, player_process));
		else if (player_process->args[counter] == DIR_CODE && !(comparator & T_DIR))
			return (move_pc(game_process->op_tab, player_process));
		else if (player_process->args[counter] == IND_CODE && !(comparator & T_IND))
			return (move_pc(game_process->op_tab, player_process));
		else if (player_process->args[counter] == 0 && (comparator))
			return (move_pc(game_process->op_tab, player_process));
		else
			counter++;
	}
	// move_pc(game_process->op_tab, player_process);
	return (true);
}

// void demonstrate(u_int8_t *reg)
// {
// 	int i;

// 	i = 3;
// 	// reg[3] = 256;
// 	// while (i < REG_SIZE * REG_NUMBER - 1)
// 	// {
// 	// 	if (i % 3 == 1 && i != 3)
// 	// 		reg[i] = 1;
// 	// 	i++;
// 	// }
// 	reg[0] = 0;
// 	reg[1] = 0;
// 	reg[2] = 0;
// 	reg[3] = 1;
// 	reg[4] = 0;
// 	reg[5] = 0;
// 	reg[6] = 0;
// 	reg[7] = 1;
// 	i = 6;
// 	while(i >= 3)
// 	{
// 		printf("%d\n", *((int *)(&reg[i])));
// 		i--;
// 	}
// 	exit(0);
// }

t_player_process *players_operations_executing(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int counter;
	t_player_process *begin;

	counter = 0;
	begin = player_process;
	// demonstrate(player_process->registers);
	while (player_process)
	{
		if (player_process->operation_code <= 16 && player_process->operation_code >= 1)
		{
			if (player_process->cycles_to_wait > 0)
				player_process->cycles_to_wait -= 1;
			if (player_process->cycles_to_wait == 0)
			{
				if (validation_before_operation_complete(game_process,
					player_process, vm_field_memory))
				{
					// operation_completer(game_process, player_process,
					// 	player_list, vm_field_memory);
					move_pc(game_process->op_tab, player_process);
					// move_pc(game_process->op_tab, player_process);
				}
				player_process->operation_code = vm_field_memory->
					field[player_process->PC];
				if ((1 <= vm_field_memory->field[player_process->PC]) &&
					(vm_field_memory->field[player_process->PC] <= 16))
					player_process->cycles_to_wait =
						(game_process->op_tab)[player_process->
								operation_code].cycles_before_complete;
			}
			// else
			// 	player_process->cycles_to_wait -= 1;
		}
		else
		{
			// printf("%llx - not valid\n", player_process->PC);
			if (player_process->PC == MEM_SIZE - 1)
				player_process->PC = 0;
			else
				player_process->PC += 1;
			player_process->operation_code = vm_field_memory->
						field[player_process->PC];
			if ((1 <= vm_field_memory->field[player_process->PC]) &&
				(vm_field_memory->field[player_process->PC] <= 16))
				player_process->cycles_to_wait =
					(game_process->op_tab)[player_process->
							operation_code].cycles_before_complete;
		}
		player_process = player_process->next;
	}
	while (begin->prev)
		begin = begin->prev;
	return(begin);
}