/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/29 17:16:17 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../parser/parser.h"

static int	_isvalidate_params(t_params *params)
{
	if (params->number_of_coders == -1 || params->time_to_burnout == -1
		|| params->time_to_compile == -1 || params->time_to_debug == -1
		|| params->time_to_refactor == -1
		|| params->number_of_compiles_required == -1
		|| params->dongle_cooldown == -1)
		return (0);
	return (1);
}

int	getparams(char **argv, t_params *params)
{
	if (!strcmp(argv[8], "edf"))
		params->scheduler = 1;
	else if (!strcmp(argv[8], "fifo"))
		params->scheduler = 2;
	else
		return (1);
	params->number_of_coders = ft_atopi(argv[1]);
	params->time_to_burnout = ft_atopi(argv[2]);
	params->time_to_compile = ft_atopi(argv[3]);
	params->time_to_debug = ft_atopi(argv[4]);
	params->time_to_refactor = ft_atopi(argv[5]);
	params->number_of_compiles_required = ft_atopi(argv[6]);
	params->dongle_cooldown = ft_atopi(argv[7]);
	if (_isvalidate_params(params))
		return (0);
	return (1);
}
