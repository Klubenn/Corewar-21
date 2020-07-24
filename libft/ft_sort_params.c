/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:47:51 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/19 21:50:11 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void		ft_sort_params(char **argv, int c)
{
	int		k;
	char	*buf;
	int		i;

	i = 1;
	while (i <= c - 1)
	{
		k = 1;
		while (k <= c - 1)
		{
			if (ft_strcmp(argv[k], argv[k + 1]) > 0)
			{
				buf = argv[k];
				argv[k] = argv[k + 1];
				argv[k + 1] = buf;
			}
			k++;
		}
		i++;
	}
}
