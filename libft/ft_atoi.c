/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:44:49 by gtapioca          #+#    #+#             */
/*   Updated: 2019/09/18 20:53:28 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned long long	checker_sign_minus(unsigned long long c)
{
	if (c > 9223372036854775807)
		return (0);
	else
	{
		c = c * -1;
		return (c);
	}
	return (c);
}

static int					create_int(char *str, int sign)
{
	unsigned long long c;

	c = 0;
	while ('0' <= *str && *str <= '9')
	{
		c = c * 10 + (*str) - '0';
		str++;
	}
	if (sign == 0)
	{
		if (c > 9223372036854775807)
			return (-1);
		else
			return (c);
	}
	if (sign == 1)
		return (checker_sign_minus(c));
	return (c);
}

static int					checker_blanks_after_signs(char *str)
{
	if (*(str + 1) == '\n' || *(str + 1) == '\r' ||
			*(str + 1) == ' ' || *(str + 1) == '\a' ||
				*(str + 1) == '\f' || *(str + 1) == '\v' ||
					*(str + 1) == '\b')
		return (0);
	return (1);
}

static char					*skipper(char *str)
{
	while ((*str == '\n' || *str == '\r' || *str == '\t' ||
			*str == ' ' || *str == '\a' || *str == '\f'
				|| *str == '\v' || *str == '\b'))
		str++;
	return (str);
}

int							ft_atoi(char *str)
{
	unsigned long long		c;
	int						sign;

	c = 0;
	sign = 0;
	str = skipper(str);
	if (!(*str))
		return (0);
	if (*str == '-' || *str == '+')
	{
		if (checker_blanks_after_signs(str) == 0)
			return (0);
		if (*str == '-')
			sign = 1;
		str++;
	}
	str = skipper(str);
	c = (int)create_int(str, sign);
	return (c);
}
