/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:30:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/02 16:28:00 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	can_eat(t_philo *philo);
static t_bool	is_sleeping(t_philo *philo, long logtime);

void	eating(t_philo *philo)
{
	while (can_eat(philo) == FALSE)
	{
		if (stop_monitor(philo))
			return ;
		usleep(DELAY);
	}
	if (take_forks(philo) == FALSE)
		return ;
	philo->meals++;
	philo->last_meal = log_state(EAT, philo);
	usleep(philo->common->time_to_eat * 1000);
	put_forks(philo);
}

void	sleeping(t_philo *philo)
{
	long	start;

	if (stop_monitor(philo))
		return ;
	start = log_state(SLEEP, philo);
	while (is_sleeping(philo, start))
	{
		if (stop_monitor(philo))
			return ;
		usleep(DELAY);
	}
}

void	thinking(t_philo *philo)
{
	if (stop_monitor(philo))
		return ;
	log_state(THINK, philo);
	while (can_eat(philo) == FALSE)
	{
		if (stop_monitor(philo))
			return ;
		usleep(DELAY);
	}
}

static t_bool	is_sleeping(t_philo *philo, long logtime)
{
	long	start_time;
	long	time_to_sleep;

	start_time = philo->common->start_time;
	time_to_sleep = philo->common->time_to_sleep;
	return (get_elapsed_time(logtime + start_time) < time_to_sleep);
}

static t_bool	can_eat(t_philo *philo)
{
	t_bool	left;
	t_bool	right;

	left = is_locked(philo->left_fork) == FALSE;
	right = is_locked(philo->right_fork) == FALSE;
	return (left && right);
}
