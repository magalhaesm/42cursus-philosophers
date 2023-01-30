/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:54:50 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/30 14:38:12 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	lock(philo->left_fork);
	lock(philo->right_fork);
	printf("%d has taken a fork\n", philo->id);
	printf("%d has taken a fork\n", philo->id);
	printf("%d is eating\n", philo->id);
}

void	put_forks(t_philo *philo)
{
	unlock(philo->left_fork);
	unlock(philo->right_fork);
}

t_fork	**arrange_forks(int philos)
{
	t_fork	**forks;

	forks = malloc(philos * sizeof(t_fork *));
	if (forks == NULL)
		return (NULL);
	while (--philos >= 0)
	{
		forks[philos] = malloc(sizeof(t_fork));
		pthread_mutex_init(&forks[philos]->mutex, NULL);
		forks[philos]->in_use = FALSE;
	}
	return (forks);
}

void	free_forks(t_fork **forks)
{
	int	guests;

	guests = get_number_of_philos();
	while (--guests >= 0)
	{
		pthread_mutex_destroy(&forks[guests]->mutex);
		free(forks[guests]);
	}
	free(forks);
}
