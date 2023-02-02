/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:28:32 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/02 13:05:17 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_common_data(t_ctrl *data);

t_bool	init_common_data(int argc, char **argv)
{
	int		*args;
	t_ctrl	data;

	args = parse(argc, argv);
	if (args == NULL)
		return (FALSE);
	data.start_time = get_current_time();
	data.n_philos = args[0];
	data.time_to_die = args[1];
	data.time_to_eat = args[2];
	data.time_to_sleep = args[3];
	data.death = FALSE;
	data.must_eat = -1;
	if (argc == 6)
		data.must_eat = args[4];
	pthread_mutex_init(&data.log, NULL);
	pthread_mutex_init(&data.notify, NULL);
	set_common_data(&data);
	free(args);
	return (TRUE);
}

int	get_number_of_philos(void)
{
	return (get_common_data()->n_philos);
}

t_ctrl	*get_common_data(void)
{
	static t_ctrl	common_data;

	return (&common_data);
}

static void	set_common_data(t_ctrl *data)
{
	t_ctrl	*common_data;

	common_data = get_common_data();
	*common_data = *data;
}
