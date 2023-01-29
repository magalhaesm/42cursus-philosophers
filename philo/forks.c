/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:54:50 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/29 16:48:36 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	fork_available(t_fork *fork)
{
	t_bool	available;

	available = TRUE;
	pthread_mutex_lock(&fork->mutex);
	if (fork->in_use)
		available = FALSE;
	pthread_mutex_unlock(&fork->mutex);
	return (available);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->left_fork->in_use = TRUE;
	philo->right_fork->in_use = TRUE;
	printf("%d has taken a fork\n", philo->id);
	printf("%d has taken a fork\n", philo->id);
	printf("%d is eating\n", philo->id);
}

void	put_forks(t_philo *philo)
{
	philo->left_fork->in_use = FALSE;
	philo->right_fork->in_use = FALSE;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
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
