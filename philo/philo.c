/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:06:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/30 14:04:29 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	t_philo	*dish;

	philos = get_number_of_philos();
	dish = malloc(philos * sizeof(t_philo));
	n = 0;
	while (n < philos)
	{
		dish[n].id = n + 1;
		dish[n].left_fork = forks[n];
		dish[n].right_fork = forks[(n + 1) % philos];
		pthread_create(threads + n, NULL, philosopher, dish + n);
		n++;
	}
	n = 0;
	while (n < philos)
	{
		pthread_join(threads[n], NULL);
		n++;
	}
	free(dish);
}

static void	*allocate_philosophers(int threads)
{
	return (malloc(threads * sizeof(pthread_t)));
}
