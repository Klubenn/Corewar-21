/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 20:29:29 by gtapioca          #+#    #+#             */
/*   Updated: 2020/07/24 14:38:58 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

void	ft_memdel(void **ap)
{
	if (!ap || !*ap)
		return ;
	free(*ap);
	*ap = 0;
}
