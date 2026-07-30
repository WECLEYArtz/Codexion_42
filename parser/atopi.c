/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atopi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:30:19 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/30 20:20:17 by wec              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_atoi_convert(const char *str)
{
	int	result;

	result = 0;
	while (*str && ft_isdigit(*str))
	{
		if ((((long)result * 10) + (*str - '0')) > INT_MAX)
			return (-1);
		else
			result = (result * 10) + (*str++ - '0');
	}
	if (*str)
		return (-1);
	return (result);
}

int	ft_atopi(const char *str)
{
	int	result;

	result = 0;
	if (*str == '-')
	{
		if (str[1] == '0' && !str[2])
			return (0);
		else
			return (-1);
	}
	else if (*str == '+')
		str++;
	result = ft_atoi_convert(str);
	return (result);
}
