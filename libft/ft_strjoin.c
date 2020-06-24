/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:10:43 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/19 08:58:29 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*snew;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	j = ft_strlen(s1);
	i = j + ft_strlen(s2) + 1;
	snew = (char *)malloc(sizeof(char) * i);
	if (!snew)
		return (NULL);
	ft_strcpy(snew, s1);
	ft_strcpy((snew + j), s2);
	return (snew);
}
