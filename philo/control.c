/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:28:32 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/07 14:11:53 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_common_data(int argc, char **argv, t_ctrl *common)
{
	int	*args;

	args = parse(argc, argv);
	if (args == NULL)
		return (FALSE);
	common->start_time = get_current_time();
	common->n_philos = args[0];
	common->time_to_die = args[1];
	common->time_to_eat = args[2];
	common->time_to_sleep = args[3];
	common->death = FALSE;
	common->must_eat = -1;
	common->stuffed = 0;
	if (argc == 6)
		common->must_eat = args[4];
	pthread_mutex_init(&common->log, NULL);
	pthread_mutex_init(&common->notify, NULL);
	pthread_mutex_init(&common->eat, NULL);
	pthread_mutex_init(&common->full, NULL);
	free(args);
	return (TRUE);
}

t_fork	**init_forks(int philos)
{
	t_fork	**forks;

	forks = malloc((philos + 1) * sizeof(t_fork *));
	if (forks == NULL)
		return (NULL);
	forks[philos] = NULL;
	while (--philos >= 0)
	{
		forks[philos] = malloc(sizeof(t_fork));
		pthread_mutex_init(&forks[philos]->mutex, NULL);
	}
	return (forks);
}

t_philo	*init_philosophers(t_ctrl *common, t_fork **forks)
{
	int		n;
	t_philo	*place;
	int		philos;

	philos = common->n_philos;
	place = malloc(philos * sizeof(t_philo));
	if (place == NULL)
		return (NULL);
	n = 0;
	while (n < philos)
	{
		place[n].id = n + 1;
		place[n].meals = 0;
		place[n].done = FALSE;
		place[n].last_meal = common->start_time;
		place[n].common = common;
		place[n].first_fork = forks[min(n, (n + 1) % philos)];
		place[n].second_fork = forks[max(n, (n + 1) % philos)];
		n++;
	}
	return (place);
}

void	free_forks(t_fork **forks)
{
	int	n;

	n = 0;
	while (forks[n])
	{
		pthread_mutex_destroy(&forks[n]->mutex);
		free(forks[n]);
		n++;
	}
	free(forks);
}
