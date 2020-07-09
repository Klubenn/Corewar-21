/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz &lt;marvin@42.fr&gt;                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;


t_op    op_tab[17] =
		{
				{NULL,0, 0, {0}, 0, 4},
				{"live", 1, 1, {T_DIR}, 0, 4},
				{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 1, 4},
				{"st", 3, 2, {T_REG, T_IND | T_REG}, 1, 4},
				{"add", 4, 3, {T_REG, T_REG, T_REG}, 1, 4},
				{"sub", 5, 3, {T_REG, T_REG, T_REG}, 1, 4},
				{"and", 6, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
				{"or", 7, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
				{"xor", 8, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
				{"zjmp", 9, 1, {T_DIR}, 0, 2},
				{"ldi", 10, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
				{"sti", 11, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
				{"fork", 12, 1, {T_DIR}, 0, 2},
				{"lld", 13, 2, {T_DIR | T_IND, T_REG}, 1, 4},
				{"lldi", 14, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
				{"lfork", 15, 1, {T_DIR}, 0, 2},
				{"aff", 16, 1, {T_REG}, 1, 4}
		};

#endif