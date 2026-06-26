/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atopi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:30:19 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/26 15:45:26 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_isspace(int c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

static int	ft_atoi_convert(const char *str)
{
	int	result;

	result = 0;
	while (*str && ft_isdigit(*str))
	{
		if ((((long)result * 10) + (*str - '0')) > INT_MAX)
			exit(puts("DEBUG: big value given"));
		else
			result = (result * 10) + (*str++ - '0');
	}
	return (result);
}

int	ft_atopi(const char *str)
{
	int	result;

	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		if (str[1] == '0' && !str[2])
			return (0);
		else
			exit(puts("DEBUG: negative value given"));
	}
	if (*str == '+')
		str++;
	result = ft_atoi_convert(str);
	return (result);
}
