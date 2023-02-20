/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:32:27 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/20 10:14:51 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	starved(t_philo *philo);
static void		notify_death(t_philo *philo);

void	*stop_monitor(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!starved(philo))
		usleep(3000);
	notify_death(philo);
	return (NULL);
}

t_bool	stop_dinner(t_philo *philo)
{
	t_ctrl	*common;

	common = philo->common;
	sem_wait(common->notify);
	if (*(long *)common->stop)
	{
		sem_post(common->notify);
		return (TRUE);
	}
	sem_post(common->notify);
	return (FALSE);
}

static void	notify_death(t_philo *philo)
{
	t_ctrl	*common;
	t_bool	display;

	display = TRUE;
	common = philo->common;
	sem_wait(common->notify);
	if (*(long *)common->stop)
		display = FALSE;
	sem_post(common->stop);
	sem_post(common->notify);
	if (display)
		state_log(DEAD, philo);
}

static t_bool	starved(t_philo *philo)
{
	int		last_meal;
	t_ctrl	*common;

	common = philo->common;
	sem_wait(common->eat);
	last_meal = get_current_time() - philo->last_meal;
	sem_post(common->eat);
	return (last_meal > common->time_to_die);
}
