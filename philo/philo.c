/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:06:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/02 13:49:30 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher(void *arg);
static void	*allocate_philosophers(int threads);
static void	start_simulation(pthread_t *threads, t_fork **forks);

int	main(int argc, char **argv)
{
	int			threads;
	t_fork		**forks;
	pthread_t	*philosophers;

	if (init_common_data(argc, argv) == FALSE)
		return (EXIT_FAILURE);
	threads = get_number_of_philos();
	philosophers = allocate_philosophers(threads);
	forks = arrange_forks(threads);
	if (philosophers && forks)
	{
		start_simulation(philosophers, forks);
		free(philosophers);
		free_forks(forks);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static void	start_simulation(pthread_t *threads, t_fork **forks)
{
	int		n;
	int		philos;
	t_philo	*place;
	t_ctrl	*common;

	common = get_common_data();
	philos = common->n_philos;
	place = malloc(philos * sizeof(t_philo));
	n = 0;
	while (n < philos)
	{
		place[n].id = n + 1;
		place[n].left_fork = forks[n];
		place[n].right_fork = forks[(n + 1) % philos];
		place[n].meals = 0;
		place[n].last_meal = 0;
		place[n].common = common;
		pthread_create(threads + n, NULL, philosopher, place + n);
		n++;
	}
	n = 0;
	while (n < philos)
		pthread_join(threads[n++], NULL);
	free(place);
}

/* Represent a philosopher who eats, thinks, sleeps and dies of starvation. */
static void	*philosopher(void *place)
{
	t_philo	*philo;

	philo = place;
	while (check_dead(philo) == FALSE)
	{
		eating(philo);
		if (philo->meals == philo->common->must_eat)
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

static void	*allocate_philosophers(int threads)
{
	return (malloc(threads * sizeof(pthread_t)));
}
