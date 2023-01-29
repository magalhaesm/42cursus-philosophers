/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:34:39 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/29 16:42:06 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	can_eat(t_philo *philo);

void	*philosopher(void *arg)
{
	t_philo	*philo;
	t_ctrl	*data;

	data = get_common_data();
	philo = arg;
	while (can_eat(philo) == FALSE)
		usleep(100);
	take_forks(philo);
	usleep(data->time_to_eat * 1000);
	put_forks(philo);
	return (NULL);
}

static t_bool	can_eat(t_philo *philo)
{
	t_bool	left;
	t_bool	right;

	left = fork_available(philo->left_fork);
	right = fork_available(philo->right_fork);
	return (left && right);
}
