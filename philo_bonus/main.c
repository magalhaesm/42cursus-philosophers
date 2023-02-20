/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:41:38 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/20 10:08:57 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define CHILD 0

static void	philosopher(t_philo *philo);
static void	start_dinner(t_philo *philos, t_ctrl *common);

int	main(int argc, char **argv)
{
	sem_t	*forks;
	t_philo	*philos;
	t_ctrl	common;

	if (!init_common_data(argc, argv, &common))
		return (EXIT_FAILURE);
	forks = init_forks(&common);
	if (!forks)
		return (EXIT_FAILURE);
	philos = init_philosophers(&common, &forks);
	if (!philos)
	{
		sem_unlink(SEM_FORKS);
		return (EXIT_FAILURE);
	}
	start_dinner(philos, &common);
	sem_free(philos);
	free(philos);
}

void	start_dinner(t_philo *philos, t_ctrl *common)
{
	int	n;

	n = 0;
	while (n < common->n_philos)
	{
		philos[n].pid = fork();
		if (philos[n].pid == CHILD)
		{
			pthread_create(&philos[n].tid, NULL, stop_monitor, philos + n);
			philosopher(philos + n);
			pthread_join(philos[n].tid, NULL);
			sem_free(philos);
			free(philos);
			exit (EXIT_SUCCESS);
		}
		n++;
	}
	n = -1;
	while (++n < common->n_philos)
		waitpid(0, NULL, 0);
}

/* Represent a philosopher who eats, thinks, sleeps and dies of starvation. */
static void	philosopher(t_philo *philo)
{
	t_ctrl	*common;

	common = philo->common;
	if (common->n_philos == 1)
	{
		state_log(TAKE_FORK, philo);
		mssleep(common->time_to_die);
		return ;
	}
	while (stop_dinner(philo) == FALSE)
	{
		eating(philo);
		if (philo->meals == common->must_eat)
			return ;
		sleeping(philo);
		thinking(philo);
	}
	return ;
}
