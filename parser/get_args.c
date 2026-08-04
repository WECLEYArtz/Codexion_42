/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/04 05:58:18 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dongle/dongle.h"
#include "../parser/parser.h"

static int	_isvalidate_args(t_args *args)
{
	if (args->number_of_coders == -1 || args->time_to_burnout == -1
		|| args->time_to_compile == -1 || args->time_to_debug == -1
		|| args->time_to_refactor == -1
		|| args->number_of_compiles_required == -1
		|| args->dongle_cooldown == -1)
		return (0);
	return (1);
}

int	get_args(char **argv, t_args *args)
{
	if (!strcmp(argv[8], "edf"))
		args->scheduler = EDF;
	else if (!strcmp(argv[8], "fifo"))
		args->scheduler = FIFO;
	else
		return (1);
	args->number_of_coders = ft_atopi(argv[1]);
	args->time_to_burnout = ft_atopi(argv[2]);
	args->time_to_compile = ft_atopi(argv[3]);
	args->time_to_debug = ft_atopi(argv[4]);
	args->time_to_refactor = ft_atopi(argv[5]);
	args->number_of_compiles_required = ft_atopi(argv[6]);
	args->dongle_cooldown = ft_atopi(argv[7]);
	if (_isvalidate_args(args))
		return (0);
	return (1);
}
