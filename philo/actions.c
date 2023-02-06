/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:30:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/06 19:47:27 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define DELAY 100

void	eating(t_philo *philo)
{
	long	last;

	pthread_mutex_lock(&philo->first_fork->mutex);
	pthread_mutex_lock(&philo->second_fork->mutex);
	if (philo->common->death)
	{
		pthread_mutex_unlock(&philo->first_fork->mutex);
		pthread_mutex_unlock(&philo->second_fork->mutex);
		return ;
	}
	philo->meals++;
	last = state_log(EATING, philo);
	pthread_mutex_lock(&philo->common->eat);
	philo->last_meal = last;
	pthread_mutex_unlock(&philo->common->eat);
	mssleep(philo->common->time_to_eat);
	pthread_mutex_unlock(&philo->first_fork->mutex);
	pthread_mutex_unlock(&philo->second_fork->mutex);
	return ;
}

void	sleeping(t_philo *philo)
{
	if (check_dead(philo))
		return ;
	state_log(SLEEPING, philo);
	mssleep(philo->common->time_to_sleep);
	return ;
}

void	thinking(t_philo *philo)
{
	if (check_dead(philo))
		return ;
	state_log(THINKING, philo);
	return ;
}

void	mssleep(long ms_time)
{
	long	start;

	start = get_current_time();
	while (ms_time > get_current_time() - start)
		usleep(DELAY);
}
