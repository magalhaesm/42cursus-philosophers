/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:06:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/08 00:27:38 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philosopher(void *arg);
static void	*set_stuffed(t_ctrl *common);
static void	start_simulation(t_ctrl *common, t_philo *place);

int	main(int argc, char **argv)
{
	t_ctrl	common;
	t_fork	**forks;
	t_philo	*philos;

	if (!init_common_data(argc, argv, &common))
		return (EXIT_FAILURE);
	forks = init_forks(common.n_philos);
	if (!forks)
		return (EXIT_FAILURE);
	philos = init_philosophers(&common, forks);
	if (philos)
	{
		start_simulation(&common, philos);
		free(philos);
	}
	free_forks(forks);
	return (common.death);
}

static void	start_simulation(t_ctrl *common, t_philo *place)
{
	int			n;
	int			philos;
	pthread_t	monitor;
	pthread_t	*threads;

	philos = common->n_philos;
	threads = malloc(philos * sizeof(pthread_t));
	if (!threads)
		return ;
	n = 0;
	while (n < philos)
	{
		pthread_create(threads + n, NULL, philosopher, place + n);
		n++;
	}
	pthread_create(&monitor, NULL, stop_monitor, &place);
	n = 0;
	while (n < philos)
		pthread_join(threads[n++], NULL);
	pthread_join(monitor, NULL);
	free(threads);
}

/* Represent a philosopher who eats, thinks, sleeps and dies of starvation. */
static void	*philosopher(void *place)
{
	t_philo	*philo;
	t_ctrl	*common;

	philo = place;
	common = philo->common;
	if (common->n_philos == 1)
	{
		state_log(TAKE_FORK, philo);
		mssleep(common->time_to_die);
		return (NULL);
	}
	while (check_dead(philo) == FALSE)
	{
		eating(philo);
		if (philo->meals == common->must_eat)
		{
			philo->done = TRUE;
			return (set_stuffed(common));
		}
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

static void	*set_stuffed(t_ctrl *common)
{
	pthread_mutex_lock(&common->full);
	common->stuffed++;
	pthread_mutex_unlock(&common->full);
	return (NULL);
}
