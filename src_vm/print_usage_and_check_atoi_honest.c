/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage_and_check_atoi_honest.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:15:03 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/25 16:04:26 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_vm/corewar.h"

void	print_usage(void)
{
	if (errno == 0)
	{
		ft_printf("Usage: ./corewar [-d N -dump N -v N] [-a] \
<champion1.cor> <...>\n\
-a   : Prints output from \"aff\" (Default is to hide it)\n\
\\#### TEXT OUTPUT MODE ###########################\
\\###############################\n\
-d N : Dumps memory 64 bytes per line after N cycles then exits\n\
-dump N : Dumps memory 32 bytes per line after N cycles then exits\n\
-v N : Verbosity levels, can be added together to enable several\n\
	- 0 : Show only essentials\n\
	- 1 : Show lives\n\
	- 2 : Show cycles\n\
	- 4 : Show operations (Params are NOT litteral ...)\n\
	- 8 : Show deaths\n\
	- 16 : Show PC movements (Except for jumps)\n%z", 2);
	}
	else
		perror("Error");
}

int		check_atoi_honest(char *argv)
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
