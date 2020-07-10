/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_executing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:14:34 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/10 19:12:59 by gtapioca         ###   ########.fr       */
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

void	op1(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	
}

void (*operation[16])(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory) =
{
	op1
};

bool	move_pc_not_valid(t_op *op_tab, t_player_process *player_process)
{
	u_int8_t	op_code;
	int counter;

	counter = 0;
	op_code = player_process->operation_code;
	while (counter < 3)
	{
		if (player_process->args[counter] == REG_CODE)
		{
			if (player_process->PC + 1 > MEM_SIZE - 1)
				player_process->PC = player_process->PC + 1 - MEM_SIZE;
			else
				player_process->PC += 1;
		}
		else if (player_process->args[counter] == IND_CODE)
		{
			if (player_process->PC + IND_SIZE > MEM_SIZE - 1)
				player_process->PC = player_process->PC + IND_SIZE - MEM_SIZE;
			else
				player_process->PC += IND_SIZE;
		}
		else if (player_process->args[counter] == DIR_CODE)
		{
			if (player_process->PC + op_tab[op_code].dir_size > MEM_SIZE - 1)
				player_process->PC = player_process->PC + op_tab[op_code].dir_size - MEM_SIZE;
			else
				player_process->PC += op_tab[op_code].dir_size;
		}
		counter++;
	}
	if (player_process->PC == MEM_SIZE - 1)
		player_process->PC = 1;
	else
		player_process->PC += 2;
	return (false);
}

// myFuncTypeArray[0] = &(lol);

bool	validation_before_operation_complete(t_game_process *game_process, t_player_process *player_process,
	t_vm_field_memory *vm_field_memory)
{
	u_int8_t	args_type_code;
	// u_int8_t	args[3];
	u_int8_t	counter;
	// u_int8_t	counter_1;
	u_int8_t	comparator;

	counter = 0;
	// counter_1 = 0;
	// if ((vm_field_memory->field)[player_process->PC] > 16 ||
	// 		(vm_field_memory->field)[player_process->PC] < 1)
	// {
	// 	player_process->PC += 1;
	// 	return (false);
	// }
	// player_process->operation_code = vm_field_memory->field[player_process->PC];
	if (game_process->op_tab[vm_field_memory->field[player_process->PC]].have_a_code_type_code == 0)
		return (true);
	// while (counter < 3)
	// {
	// 	if (game_process->op_tab[vm_field_memory->field[player_process->PC]].arg_types[counter] != 0)
	// 		counter_1++;
	// 	counter++;
	// }
	// if (counter_1 == 1)
	// 	return (true);
	// counter = 0;
	if (player_process->PC == MEM_SIZE - 1)
		args_type_code = (vm_field_memory->field)[0];
	else
		args_type_code = (vm_field_memory->field)[player_process->PC + 1];
	player_process->args[0] = (args_type_code & 192) >> 6;
	player_process->args[1] = (args_type_code & 48) >> 4;
	player_process->args[2] = (args_type_code & 12) >> 2;
	// if (game_process->op_tab[vm_field_memory->field[player_process->PC]].arg_types[0])
	while (counter < 3)
	{
		comparator = (game_process->op_tab)[player_process->operation_code].arg_types[counter];
		if (player_process->args[counter] == REG_CODE && (comparator == T_DIR || comparator == (T_DIR | T_IND) ||
			comparator == T_IND || comparator == 0))
			return (move_pc_not_valid(game_process->op_tab, player_process));
		else if (player_process->args[counter] == DIR_CODE && (comparator == T_REG || comparator == T_IND ||
			comparator == (T_REG | T_IND) || comparator == 0))
			return (move_pc_not_valid(game_process->op_tab, player_process));
		else if (player_process->args[counter] == IND_CODE && (comparator == T_REG || comparator == T_DIR ||
			comparator == (T_REG | T_DIR) || comparator == 0))
			return (move_pc_not_valid(game_process->op_tab, player_process));
		else if (player_process->args[counter] == 0 && (comparator == T_REG || comparator == T_DIR ||
			comparator == T_IND || comparator == (T_REG | T_DIR) || comparator == (T_DIR | T_IND) ||
				comparator == (T_REG | T_DIR | T_IND)))
			return (move_pc_not_valid(game_process->op_tab, player_process));
		else
			counter++;
	}
	move_pc_not_valid(game_process->op_tab, player_process);
	return (true);
}

void players_operations_executing(t_game_process *game_process, t_player_process *player_process,
	t_player_list *player_list, t_vm_field_memory *vm_field_memory)
{
	int counter;

	counter = 0;
	while (player_process)
	{
		if (player_process->operation_code <= 16 && player_process->operation_code >= 1)
		{
		// while (counter < 17)
		// {
			// if (player_process->operation_code ==
			// 	game_process->op_tab[counter].bytecode_operation)
			// {
				if (player_process->cycles_to_wait == 0)
				{
					// printf("%llx\n", player_process->PC);
					if (validation_before_operation_complete(game_process, player_process, vm_field_memory))
					{
						// if (player_process->PC == MEM_SIZE - 1)
						// 	player_process->PC = 0;
						// else
						// 	player_process->PC += 1;
					}
						// operation[counter](game_process,
						// 	player_process, player_list,
						// 		vm_field_memory);
					player_process->operation_code = vm_field_memory->
						field[player_process->PC];
					if ((1 <= vm_field_memory->field[player_process->PC]) &&
						(vm_field_memory->field[player_process->PC] <= 16))
						player_process->cycles_to_wait =
							(game_process->op_tab)[player_process->
									operation_code].cycles_before_complete;
					// if (player_process->PC == MEM_SIZE - 1)
					// 	player_process->operation_args_type = vm_field_memory->field[0];
					// else
					// 	player_process->operation_args_type = vm_field_memory->field[player_process->PC + 1];
				}
				else
					player_process->cycles_to_wait -= 1;
			// }
			// counter++;
		// }
		}
		else
		{
			printf("%llx - not valid\n", player_process->PC);
			if (player_process->PC == MEM_SIZE - 1)
				player_process->PC = 0;
			else
				player_process->PC += 1;
			// printf("%llu\n", player_process->PC);
			player_process->operation_code = vm_field_memory->
						field[player_process->PC];
			if ((1 <= vm_field_memory->field[player_process->PC]) &&
				(vm_field_memory->field[player_process->PC] <= 16))
				player_process->cycles_to_wait =
					(game_process->op_tab)[player_process->
							operation_code].cycles_before_complete;
		}
		// else
		// {
		// 	player_process->PC += 1;
		// 	player_process->cycles_to_wait = (vm_field_memory->field)[player_process->PC]
		// 	player_process->cycles_to_wait -= 1;
		// }
		player_process = player_process->next;
	}
}