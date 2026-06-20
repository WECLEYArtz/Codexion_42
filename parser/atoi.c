/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:30:19 by ahmounsi          #+#    #+#             */
/*   Updated: 2025/10/29 00:59:47 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_isspace(int c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

static long	ft_atoi_convert(const char *str, int sign)
{
	long	result;

	result = 0;
	while (*str && ft_isdigit(*str))
	{
		if ((long)((result * 10) + (long)(*str - '0')) < result)
		{
			if (sign == -1)
				return (0);
			else
				return (-1);
		}
		else
			result = (result * 10) + (*str++ - '0');
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || (*str == '-'))
	{
		if (*str == '-')
			(sign = -1);
		str++;
	}
	result = ft_atoi_convert(str, sign);
	return (result * sign);
}
