/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:30:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/20 10:47:08 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	size_t	last;

	pthread_mutex_lock(&philo->first_fork->mutex);
	pthread_mutex_lock(&philo->second_fork->mutex);
	if (stop_dinner(philo))
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
	if (stop_dinner(philo))
		return ;
	state_log(SLEEPING, philo);
	mssleep(philo->common->time_to_sleep);
	return ;
}

void	thinking(t_philo *philo)
{
	if (stop_dinner(philo))
		return ;
	state_log(THINKING, philo);
	return ;
}
