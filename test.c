/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:53:54 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/21 23:24:10 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdbool.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include "corewar.h"
#include "libft/libft.h"
#include <fcntl.h>
// #include "get_next_line/get_next_line.h"
#include "op.h"

void print_usage()
{
	if (errno == 0)
		fprintf(stderr, "Usage: ./corewar [-d N -dump N -v N] [-a] <champion1.cor> <...>\n\
 -a   : Prints output from \"aff\" (Default is to hide it)\n\
#### TEXT OUTPUT MODE ##########################################################\n\
 -d N : Dumps memory 64 bytes per line after N cycles then exits\n\
 -dump N : Dumps memory 32 bytes per line after N cycles then exits\n\
 -v N : Verbosity levels, can be added together to enable several\n\
	- 0 : Show only essentials\n\
	- 1 : Show lives\n\
	- 2 : Show cycles\n\
	- 4 : Show operations (Params are NOT litteral ...)\n\
	- 8 : Show deaths\n\
	- 16 : Show PC movements (Except for jumps)\n");
	else
		perror("Error");
}

void read_code(int fd, char *str, t_player *player, int count)
{
	str = str + 2192;
	int i;
	int j;

	i = 0;
	j = 0;
	player->code = (unsigned char *)ft_memalloc(count);
	// ft_printf("code size = %x\n", player->player_header.prog_size);
	while (i < player->player_header.prog_size)
	{
		player->code[i] = str[i];
		i++;
	}
	// while (j < player->player_header.prog_size)
	// {
	// 	if ((player->code[j]) >= 16)
	// 		ft_printf("%x ", (player->code[j]));
	// 	else
	// 		ft_printf("0%x ", (player->code[j]));
	// 	j++;
	// 	if (j % 8 == 0 && j % 16 != 0)
	// 		ft_printf("  ");
	// 	if (j % 16 == 0)
	// 		ft_printf("\n");
	// }
	// ft_printf("\n");
}

void read_comment(char *str, t_player *player)
{
	int i;

	i = 0;
	while (i < COMMENT_LENGTH)
	{
		player->player_header.comment[i] = str[i + 12 + PROG_NAME_LENGTH];
		i++;
	}
	// ft_printf("comment - %s\n", player->player_header.comment);
}

int check_nulls_and_code_size(int count, char *str, t_player *player, char **argv)
{
	int i;
	int j;
	unsigned char *code_size_point;

	i = 139;
	j = 0;
	if (str[4 + PROG_NAME_LENGTH] != 0 | str[5 + PROG_NAME_LENGTH] != 0
		| str[6 + PROG_NAME_LENGTH] != 0 | str[7 + PROG_NAME_LENGTH] != 0
			| str[12 + PROG_NAME_LENGTH + COMMENT_LENGTH] != 0 | str[13 + PROG_NAME_LENGTH + COMMENT_LENGTH] != 0
		  		| str[14 + PROG_NAME_LENGTH + COMMENT_LENGTH] != 0 | str[15 + PROG_NAME_LENGTH + COMMENT_LENGTH] != 0)
	{
		fprintf(stderr, "Error : mistake in the separating nulls\n");
		// exit(1);
		return (1);
	}
	if (!(code_size_point = (unsigned char *)ft_memalloc(4)))
		return (1);
	while (j < 4)
	{
		code_size_point[j] = str[11 + PROG_NAME_LENGTH - j];
		j++;
	}
	if ((*((unsigned int *)(code_size_point))) > CHAMP_MAX_SIZE)
	{
		fprintf(stderr, "Error: File %s has too large a code (%d bytes > %d bytes)\n",
			*argv, (*((unsigned int *)(code_size_point))), CHAMP_MAX_SIZE);
		free(code_size_point);
		// errno = 1000;
		// write(2, "pipec\n", 6);
		// exit (1);
		return (1);
	}
	else if (count != (*((unsigned int *)(code_size_point))))
	{
		fprintf(stderr, "Error: File %s has a code size that differ from what its header says\n", *argv);
		free(code_size_point);
		// exit (1);
		return (1);
	}
	else
	{
		// player->code_size = (*((unsigned int *)(code_size_point)));
		player->player_header.prog_size = (*((unsigned int *)(code_size_point)));
		free(code_size_point);
		// free(code_size_point);
		return (0);
	}
}

void set_player_name(char *str, t_player *player)
{
	int i;

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		player->player_header.prog_name[i] = str[i + 4];
		i++;
	}
	player->player_header.prog_name[PROG_NAME_LENGTH] = '\0';
}

int check_magic_header(char *str, char **argv, t_player *player)
{
	char helper[4];

	if ((unsigned char)str[0] != 0x00 | (unsigned char)str[1] != 0xea
		| (unsigned char)str[2] != 0x83 | (unsigned char)str[3] != 0xf3)
	{
		fprintf(stderr, "Error: File %s has an invalid header\n", *argv);
		return (1);
	}
	helper[0] = str[3];
	helper[1] = str[2];
	helper[2] = str[1];
	helper[3] = str[0];	
	player->player_header.magic = *((unsigned int *)helper);
	return(0);
}

int players_reader_parse_champions(int fd, t_player *player, char **argv)
{
	char str[BUFFER_SIZE];
	int c;
	int count;

	count = 0;
	while ((c = read(fd, str, BUFFER_SIZE)))
		count = count + c;
	count = count - PROG_NAME_LENGTH - COMMENT_LENGTH - 16;
	lseek(fd, 0, SEEK_SET);
	read(fd, str, BUFFER_SIZE);
	if (check_magic_header(str, argv, player))
		return(1);
	set_player_name(str, player);
	if (check_nulls_and_code_size(count, str, player, argv) == 0)
	{
		read_comment(str, player);
		read_code(fd, str, player, count);
		return (0);
	}
	return (1);
}



int put_in_stack_of_players_helper(t_player_list **player_list, t_player *player, int pos)
{
	t_player_list	*buff;
	t_player_list	*player_list_loc;

	player_list_loc = *player_list;
	if (player_list_loc == NULL)
	{
		if (!(*player_list = (t_player_list *)ft_memalloc(sizeof(t_player_list))))
			return (1);
		(*player_list)->player = player;
		(*player_list)->next = NULL;
		(*player_list)->prev = NULL;
		if (pos > 0)
			(*player_list)->position = pos;
		else
			(*player_list)->position = 0;
		return (0);
	}
	else
	{
		while (player_list_loc->next != 0)
			player_list_loc = player_list_loc->next;
		if (pos == player_list_loc->position && pos != 0)
		{
			print_usage();
			return (1);
		}
		if (!(player_list_loc->next = (t_player_list *)ft_memalloc(sizeof(t_player_list))))
			return (1);
		player_list_loc->next->prev = player_list_loc;
		player_list_loc = player_list_loc->next;
		player_list_loc->player = player;
		player_list_loc->next = NULL;
		if (pos > 0)
			player_list_loc->position = pos;
		else
			player_list_loc->position = 0;
		return (0);
	}
}

int put_in_stack_of_players(int pos, char *player_name, t_player_list **player_list)
{
	t_player	*player;
	int				fd;

	fd = open(player_name, O_RDONLY);
	if (ft_strstr(player_name, ".cor") == NULL)
	{
		if (errno == 0)
			fprintf(stderr, "Wrong file format %s\n", player_name);
		else
			perror("Error");
		return (1);
	}
	if (fd < 0)
	{
		if (errno == 0)
			fprintf(stderr, "Can't read source file %s\n", player_name);
		else
			perror("Error");
		return (1);
	}
	if (!(player = (t_player *)ft_memalloc(sizeof(t_player))))
	{
		perror("Error");
		return(1);
	}
	if (players_reader_parse_champions(fd, player, &player_name))
	{
		free(player);
		return (1);
	}
	close(fd);
	if (put_in_stack_of_players_helper(player_list, player, pos))
	{
		if (errno != 0)
			perror("Error");
		return (1);
	}
	return (0);
}

int check_atoi_honest(char *argv)
{
	while (*argv == '\t' || *argv == '\v' || *argv == '\f' ||
			*argv == '\r' || *argv == '\n' || *argv == ' ')
		argv++;
	if (*argv == '-' || *argv == '+')
		argv++;
	while (*argv == '0' && *(argv + 1) == '0')
		argv++;
	while (*argv >= '0' && *argv <= '9')
		argv++;
	if (*argv != '\0')
		return (0);
	return (1);
}

t_player_list *stack_deleter(t_player_list *player_list, int flag)
{
	t_player_list *returner;
	t_player_list *deleter;

	returner = NULL;
	if (player_list->next != 0 && player_list->prev != 0)
	{
		player_list->prev->next = player_list->next;
		player_list->next->prev = player_list->prev;
		returner = player_list->prev;
		free(player_list);
	}
	else if (player_list->next == 0 && player_list->prev != 0)
	{
		player_list->prev->next = NULL;
		returner = player_list->prev;
		free(player_list);
	}
	else if (player_list->next != 0 && player_list->prev == 0)
	{
		player_list->next->prev = NULL;
		returner = player_list->next;
		free(player_list);
	}
	else if (player_list->next == 0 && player_list->prev == 0)
		free(player_list);
	if (flag == 0)
	{
		while (returner != NULL && returner->prev != NULL)
			returner = returner->prev;
	}
	return(returner);
}

t_player_list *player_stack_creator(t_player_list *player_list_1,
	t_player_list *player_list_2, t_game_process *game_process)
{
	t_player_list *player_list_final;
	t_player_list *player_list_buff;
	int count;

	count = 1;
	player_list_final = NULL;
	player_list_buff = player_list_2;
	while (player_list_1 != NULL || player_list_2 != NULL)
	{
		player_list_buff = player_list_2;
		while (player_list_buff && player_list_buff->position != count)
			player_list_buff = player_list_buff->next;
		if (player_list_buff != NULL)
		{
			if (player_list_final == NULL)
			{
				if (!(player_list_final = (t_player_list *)ft_memalloc(sizeof(t_player_list))))
				{
					memory_deleter(player_list_1, 0, 0);
					memory_deleter(player_list_2, 0, 0);
					memory_deleter(game_process->begin_list, 0, game_process);
					perror("Error");
					exit(1);
				}
				player_list_final->player = player_list_buff->player;
				player_list_final->position = player_list_buff->position;
				player_list_final->next = NULL;
				player_list_final->prev = NULL;
				// player_list_final->player->last_live_cycle_number = 0;
				game_process->begin_list = player_list_final;
				player_list_2 = stack_deleter(player_list_buff, 0);
			}
			else
			{
				if (!(player_list_final->next = (t_player_list *)ft_memalloc(sizeof(t_player_list))))
				{
					memory_deleter(player_list_1, 0, 0);
					memory_deleter(player_list_2, 0, 0);
					memory_deleter(game_process->begin_list, 0, game_process);
					perror("Error");
					exit(1);
				}
				player_list_final->next->prev = player_list_final;
				player_list_final = player_list_final->next;
				player_list_final->player = player_list_buff->player;
				player_list_final->position = player_list_buff->position;
				player_list_final->next = NULL;
				// player_list_final->player->last_live_cycle_number = 0;
				player_list_2 = stack_deleter(player_list_buff, 0);
			}
		}
		else
		{
			if (player_list_final == NULL)
			{
				if (!(player_list_final = (t_player_list *)ft_memalloc(sizeof(t_player_list))))
				{
					memory_deleter(player_list_1, 0, 0);
					memory_deleter(player_list_2, 0, 0);
					memory_deleter(game_process->begin_list, 0, game_process);
					perror("Error");
					exit(1);
				}
				player_list_final->player = player_list_1->player;
				player_list_final->position = count;
				player_list_final->next = NULL;
				player_list_final->prev = NULL;
				// player_list_final->player->last_live_cycle_number = 0;
				game_process->begin_list = player_list_final;
				player_list_1 = stack_deleter(player_list_1, 1);
			}
			else
			{
				if (!(player_list_final->next = (t_player_list *)ft_memalloc(sizeof(t_player_list))))
				{
					memory_deleter(player_list_1, 0, 0);
					memory_deleter(player_list_2, 0, 0);
					memory_deleter(game_process->begin_list, 0, game_process);
					perror("Error");
					exit(1);
				}
				player_list_final->next->prev = player_list_final;
				player_list_final = player_list_final->next;
				player_list_final->player = player_list_1->player;
				player_list_final->position = count;
				player_list_final->next = NULL;
				// player_list_final->player->last_live_cycle_number = 0;
				player_list_1 = stack_deleter(player_list_1, 1);
			}
		}
		count++;
	}
	return (game_process->begin_list);
}

int check_position(t_player_list *player_list_1, t_player_list *player_list_2)
{
	int len;

	len = 0;
	while (player_list_1 != 0)
	{
		len++;
		player_list_1 = player_list_1->next;
	}
	player_list_1 = player_list_2;
	while (player_list_1 != 0)
	{
		len++;
		player_list_1 = player_list_1->next;
	}
	if (len > MAX_PLAYERS)
	{
		if (errno == 0)
			fprintf(stderr, "Too many champions\n");
		else
			perror("Error");
		return (1);
	}
	while (player_list_2 != 0)
	{
		if (player_list_2->position > len)
		{
			print_usage();
			return (1);
		}
		player_list_2 = player_list_2->next;
	}
	if (len == 0)
	{
		print_usage();
		return (1);
	}
	return (0);
}

void parse_arguments(char **argv, t_game_process *game_process, t_player_list **player_list)
{
	char		**begin_buff_argv;
	t_player_list *player_list_1;
	t_player_list *player_list_2;
	int count_dump;
	int count_d;
	int count_v;

	begin_buff_argv = argv;
	count_dump = 0;
	count_d = 0;
	count_v = 0;
	player_list_1 = NULL;
	player_list_2 = NULL;
	game_process->flag_a  = false;
	game_process->dump_cycle  = 0;
	game_process->d_cycle  = 0;
	while (*argv != 0)
	{
		if (ft_strcmp(*argv, "-dump") == 0)
		{
			argv++;
			if (*argv && ft_atoi(*argv) >= 0 &&
					check_atoi_honest(*argv) == 1 &&
						count_dump == 0 && count_d == 0)
			{
				game_process->dump_cycle = ft_atoi(*argv);
				game_process->bytes_dump_per_line = 32;
				game_process->dump_flag = true;
				count_dump++;
			}
			else
			{
				memory_deleter(player_list_2, 0, game_process);
				memory_deleter(player_list_1, 0, 0);
				arguments_memory_deleter(begin_buff_argv);
				print_usage();
				exit(1);
			}
		}
		else if (ft_strcmp(*argv, "-d") == 0)
		{
			argv++;
			if (*argv && ft_atoi(*argv) >= 0 &&
					check_atoi_honest(*argv) == 1 &&
						count_dump == 0 && count_d == 0)
			{
				game_process->d_cycle = ft_atoi(*argv);
				game_process->bytes_dump_per_line = 64;
				game_process->dump_flag = true;
				count_d++;
			}
			else
			{
				memory_deleter(player_list_1, 0, 0);
				arguments_memory_deleter(begin_buff_argv);
				memory_deleter(player_list_2, 0, game_process);
				print_usage();
				// errno = -1;
				// return (1);
				exit(1);
			}
		}
		else if (ft_strcmp(*argv, "-n") == 0)
		{
			argv++;
			if (*argv && ft_atoi(*argv) > 0 && ft_atoi(*argv) <= 4 &&
					check_atoi_honest(*argv) == 1 && *(argv + 1) &&
						ft_strcmp(*(argv + 1), "-n") != 0)
			{
				argv++;
				if (put_in_stack_of_players(ft_atoi(*(argv - 1)), *argv, &player_list_2))
				{
					memory_deleter(player_list_1, 0, 0);
					memory_deleter(player_list_2, 0, game_process);
					arguments_memory_deleter(begin_buff_argv);
					exit(1);
				}
			}
			else
			{
				memory_deleter(player_list_1, 0, 0);
				memory_deleter(player_list_2, 0, game_process);
				arguments_memory_deleter(begin_buff_argv);
				print_usage();
				exit(1);
				// return (1);
			}
		}
		else if (ft_strcmp(*argv, "-a") == 0)
			game_process->flag_a = true;
		else if (ft_strcmp(*argv, "-v") == 0)
		{
			if (*(argv + 1) != 0 && count_v == 0)
				game_process->flag_v = (uint8_t)(ft_atoi(*(argv + 1)));
			else
			{
				memory_deleter(player_list_1, 0, 0);
				memory_deleter(player_list_2, 0, game_process);
				arguments_memory_deleter(begin_buff_argv);
				print_usage();
				exit(1);
				// return (1);
			}
			argv++;
			count_v++;
		}
		else
		{
			if (put_in_stack_of_players(0, *argv, &player_list_1))
			{
				memory_deleter(player_list_1, 0, 0);
				memory_deleter(player_list_2, 0, game_process);
				arguments_memory_deleter(begin_buff_argv);
				exit(1);
			}
		}
		argv++;
	}
	arguments_memory_deleter(begin_buff_argv);
	if (check_position(player_list_1, player_list_2))
	{
		memory_deleter(player_list_1, 0, 0);	
		memory_deleter(player_list_2, 0, game_process);
		exit(1);
	}
	*player_list = player_stack_creator(player_list_1, player_list_2, game_process);
}

size_t	ft_count_words(char const *s, char c)
{
	size_t words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

void free_memory_after_strsplit(char **argv)
{
	char **beginner;

	beginner = argv;
	while (*argv != 0)
	{
		free(*argv);
		argv++;
	}
	free(*argv);
	free(beginner);
}

void memory_allocator_helper(char *str, char **buff)
{
	char **buff_begin;
	char **buff_2;
	int i;
	int j;

	j = 0;
	buff_begin = buff;
	while(*buff != 0)
		buff++;
	if (!(buff_2 = ft_strsplit(str, ' ')))
	{
		arguments_memory_deleter(buff);
		perror("Error");
		exit(1);
	}
	while (buff_2[j] != 0)
	{
		i = 0;
		if (!(*buff = (char *)ft_memalloc(sizeof(char)*(ft_strlen(buff_2[j]) + 1))))
		{
			arguments_memory_deleter(buff_begin);
			arguments_memory_deleter(buff_2);
			perror("Error");
			exit(1);
		}
		while (buff_2[j][i] != 0)
		{
			(*buff)[i] = buff_2[j][i];
			i++;
		}
		(*buff)[i] = 0;
		j++;
		buff++;
	}
	arguments_memory_deleter(buff_2);
}