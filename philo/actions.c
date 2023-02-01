/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:30:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/31 21:02:38 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	can_eat(t_philo *philo);

void	eating(t_philo *philo)
{
	while (can_eat(philo) == FALSE)
		usleep(DELAY);
	take_forks(philo);
	log_state(EATING, philo);
	usleep(get_common_data()->time_to_eat * 1000);
	put_forks(philo);
}

void	sleeping(t_philo *philo)
{
	log_state(SLEEPING, philo);
	usleep(get_common_data()->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	log_state(THINKING, philo);
	while (can_eat(philo) == FALSE)
		usleep(DELAY);
}

static t_bool	can_eat(t_philo *philo)
{
	t_bool	left;
	t_bool	right;

	left = is_locked(philo->left_fork) == FALSE;
	right = is_locked(philo->right_fork) == FALSE;
	return (left && right);
}
