/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:30:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/06 14:17:29 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mssleep(long ms_time)
{
	long	start;

	start = get_current_time();
	while (ms_time > get_current_time() - start)
		usleep(DELAY);
	return (0);
}

t_bool	eating(t_philo *philo)
{
	long	last;

	if (check_dead(philo))
		return (FALSE);
	pthread_mutex_lock(&philo->first_fork->mutex);
	pthread_mutex_lock(&philo->second_fork->mutex);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&philo->first_fork->mutex);
		pthread_mutex_unlock(&philo->second_fork->mutex);
		return (FALSE);
	}
	philo->meals++;
	last = state_log(EATING, philo);
	pthread_mutex_lock(&philo->common->eat);
	philo->last_meal = last;
	pthread_mutex_unlock(&philo->common->eat);
	mssleep(philo->common->time_to_eat);
	pthread_mutex_unlock(&philo->first_fork->mutex);
	pthread_mutex_unlock(&philo->second_fork->mutex);
	return (TRUE);
}

t_bool	sleeping(t_philo *philo)
{
	if (check_dead(philo))
		return (FALSE);
	state_log(SLEEPING, philo);
	mssleep(philo->common->time_to_sleep);
	return (TRUE);
}

t_bool	thinking(t_philo *philo)
{
	if (check_dead(philo))
		return (FALSE);
	state_log(THINKING, philo);
	return (TRUE);
}
