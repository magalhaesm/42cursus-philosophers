/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:32:27 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/02 14:08:57 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	starved(t_philo *philo);
static void		notify_death(t_philo *philo);

t_bool	stop_monitor(t_philo *philo)
{
	if (starved(philo))
	{
		notify_death(philo);
		return (TRUE);
	}
	if (check_dead(philo))
		return (TRUE);
	return (FALSE);
}

t_bool	check_dead(t_philo *philo)
{
	t_bool	death;
	t_ctrl	*common;

	death = FALSE;
	common = philo->common;
	pthread_mutex_lock(&common->notify);
	if (common->death)
		death = TRUE;
	pthread_mutex_unlock(&common->notify);
	return (death);
}

static void	notify_death(t_philo *philo)
{
	t_ctrl	*common;

	common = philo->common;
	pthread_mutex_lock(&common->notify);
	if (common->death == FALSE)
	{
		philo->common->death = TRUE;
		log_state(DEATH, philo);
	}
	pthread_mutex_unlock(&common->notify);
}

static t_bool	starved(t_philo *philo)
{
	long	last_meal;

	last_meal = get_elapsed_time(philo->common->start_time + philo->last_meal);
	return (last_meal >= philo->common->time_to_die);
}
