/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:28:32 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/29 12:49:44 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_control_data(t_ctrl *data);

t_bool	init_control_data(int argc, char **argv)
{
	int		*args;
	t_ctrl	data;

	args = parse(argc, argv);
	if (args == NULL)
		return (FALSE);
	data.n_philos = args[0];
	data.time_to_die = args[1];
	data.time_to_eat = args[2];
	data.time_to_sleep = args[3];
	if (argc == 6)
		data.meals = args[4];
	set_control_data(&data);
	free(args);
	return (TRUE);
}

t_ctrl	*get_control_data(void)
{
	static t_ctrl	shared_data;

	return (&shared_data);
}

static void	set_control_data(t_ctrl *data)
{
	t_ctrl	*shared_data;

	shared_data = get_control_data();
	*shared_data = *data;
}
