/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:30:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/19 22:39:33 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define DELAY 100

void	eating(t_philo *philo)
{
	size_t	last;

	sem_wait(philo->left_fork);
	sem_wait(philo->right_fork);
	if (stop_dinner(philo))
	{
		sem_post(philo->left_fork);
		sem_post(philo->right_fork);
		return ;
	}
	philo->meals++;
	last = state_log(EATING, philo);
	sem_wait(philo->common->eat);
	philo->last_meal = last;
	sem_post(philo->common->eat);
	mssleep(philo->common->time_to_eat);
	sem_post(philo->right_fork);
	sem_post(philo->left_fork);
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

void	mssleep(size_t ms_time)
{
	size_t	start;

	start = get_current_time();
	while (ms_time > get_current_time() - start)
		usleep(DELAY);
}
