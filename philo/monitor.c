/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:32:27 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/07 14:34:41 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	starved(t_philo *philo);
static t_bool	all_stuffed(t_ctrl *common);
static void		notify_death(t_philo *philo);

void	*stop_monitor(void *arg)
{
	int		index;
	t_ctrl	*common;
	t_philo	*philos;

	philos = *(t_philo **)arg;
	common = philos[0].common;
	while (all_stuffed(common) == FALSE)
	{
		index = 0;
		while (index < common->n_philos)
		{
			if (starved(&philos[index]))
			{
				notify_death(&philos[index]);
				return (NULL);
			}
			index++;
		}
		usleep(3000);
	}
	return (NULL);
}

t_bool	check_dead(t_philo *philo)
{
	t_ctrl	*common;

	common = philo->common;
	pthread_mutex_lock(&common->notify);
	if (common->death)
	{
		pthread_mutex_unlock(&common->notify);
		return (TRUE);
	}
	pthread_mutex_unlock(&common->notify);
	return (FALSE);
}

static void	notify_death(t_philo *philo)
{
	t_ctrl	*common;

	common = philo->common;
	pthread_mutex_lock(&common->notify);
	if (common->death == FALSE)
		philo->common->death = TRUE;
	pthread_mutex_unlock(&common->notify);
	state_log(DEAD, philo);
}

static t_bool	starved(t_philo *philo)
{
	int		last_meal;
	t_ctrl	*common;

	common = philo->common;
	pthread_mutex_lock(&common->eat);
	last_meal = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&common->eat);
	return (last_meal > common->time_to_die && philo->done == FALSE);
}

static t_bool	all_stuffed(t_ctrl *common)
{
	t_bool	stuffed;

	stuffed = FALSE;
	pthread_mutex_lock(&common->full);
	if (common->stuffed == common->n_philos)
		stuffed = TRUE;
	pthread_mutex_unlock(&common->full);
	return (stuffed);
}
