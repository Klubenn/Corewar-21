/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_executing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:14:34 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/09 22:22:52 by gtapioca         ###   ########.fr       */
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

bool	move_pc_not_valid(t_op *op_tab, t_player_process *player_process, u_int8_t *args)
{
	u_int8_t	op_code;
	int counter;

	counter = 0;
	op_code = player_process->PC;
	while (counter < 3)
	{
		if (args[counter] == T_REG)
		{
			if (player_process->PC + REG_SIZE > MEM_SIZE - 1)
				player_process->PC = player_process->PC + REG_SIZE - MEM_SIZE;
			else
				player_process->PC += REG_SIZE;
		}
		else if (args[counter] == T_IND)
		{
			if (player_process->PC + IND_SIZE > MEM_SIZE - 1)
				player_process->PC = player_process->PC + IND_SIZE - MEM_SIZE;
			else
				player_process->PC += IND_SIZE;
		}
		else if (args[counter] == T_DIR)
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
	u_int8_t	args[3];
	u_int8_t	counter;
	u_int8_t	comparator;

	counter = 0;
	
	if ((vm_field_memory->field)[player_process->PC] > 16 || (vm_field_memory->field)[player_process->PC] < 1)
	{
		player_process->PC += 1;
		return (false);
	}
	if (player_process->PC == MEM_SIZE - 1)
		args_type_code = (vm_field_memory->field)[0];
	else
		args_type_code = (vm_field_memory->field)[player_process->PC];
	args[0] = (args_type_code & 12) >> 2;
	args[1] = (args_type_code & 48) >> 4;
	args[2] = (args_type_code & 192) >> 6;
	while (counter < 3)
	{
		comparator = (game_process->op_tab)[(vm_field_memory->field)[player_process->PC]].arg_types[counter];
		if (args[counter] == T_REG && (comparator == T_DIR || comparator == (T_DIR | T_IND) ||
			comparator == T_IND || comparator == 0)) 
			return (move_pc_not_valid(game_process->op_tab, player_process, args));
		else if (args[counter] == T_DIR && (comparator == T_REG || comparator == T_IND ||
			comparator == (T_REG | T_IND) || comparator == 0)) 
			return (move_pc_not_valid(game_process->op_tab, player_process, args));
		else if (args[counter] == T_IND && (comparator == T_REG || comparator == T_DIR ||
			comparator == (T_REG | T_DIR) || comparator == 0))
			return (move_pc_not_valid(game_process->op_tab, player_process, args));
		else if (args[counter] == 0 && (comparator == T_REG || comparator == T_DIR ||
			comparator == T_IND || comparator == (T_REG | T_DIR) || comparator == (T_DIR | T_IND) ||
				comparator == (T_REG | T_DIR | T_IND)))
			return (move_pc_not_valid(game_process->op_tab, player_process, args));
		else
			counter++;
	}
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
					printf("%llu\n", player_process->PC);
					if (validation_before_operation_complete(game_process, player_process, vm_field_memory))
						player_process->PC += 1;
						// operation[counter](game_process,
						// 	player_process, player_list,
						// 		vm_field_memory);
					player_process->operation_code = vm_field_memory->
						field[player_process->PC];
					if ((1 <= vm_field_memory->field[player_process->PC]) &&
						(vm_field_memory->field[player_process->PC] <= 16))
						player_process->cycles_to_wait =
							(game_process->op_tab)[vm_field_memory->
								field[player_process->
									operation_code]].cycles_before_complete;
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
			player_process->PC += 1;
			player_process->operation_code = vm_field_memory->
						field[player_process->PC];
			if ((1 <= vm_field_memory->field[player_process->PC]) &&
				(vm_field_memory->field[player_process->PC] <= 16))
				player_process->cycles_to_wait =
					(game_process->op_tab)[vm_field_memory->
						field[player_process->
							operation_code]].cycles_before_complete;
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