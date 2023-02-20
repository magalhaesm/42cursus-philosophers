/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:07:54 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/20 10:31:27 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define SEM_NOTIFY "/sem_notify"
#define SEM_LOG "/sem_log"
#define SEM_EAT "/sem_eat"
#define SEM_STOP "/sem_stop"

static void	sem_clean(void);

t_bool	init_common_data(int argc, char **argv, t_ctrl *common)
{
	int	*args;

	sem_clean();
	args = parse(argc, argv);
	if (args == NULL)
		return (FALSE);
	common->start_time = get_current_time();
	common->n_philos = args[0];
	common->time_to_die = args[1];
	common->time_to_eat = args[2];
	common->time_to_sleep = args[3];
	common->must_eat = -1;
	if (argc == 6)
		common->must_eat = args[4];
	common->notify = sem_open(SEM_NOTIFY, O_CREAT, 0644, 1);
	common->log = sem_open(SEM_LOG, O_CREAT, 0644, 1);
	common->eat = sem_open(SEM_EAT, O_CREAT, 0644, 1);
	common->stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
	common->forks = sem_open(SEM_FORKS, O_CREAT, 0644, common->n_philos);
	free(args);
	return (TRUE);
}

sem_t	*init_forks(t_ctrl *common)
{
	sem_t	*forks;

	sem_unlink(SEM_FORKS);
	forks = sem_open(SEM_FORKS, O_CREAT, 0644, common->n_philos);
	if (!forks)
		return (NULL);
	return (forks);
}

t_philo	*init_philosophers(t_ctrl *common, sem_t **forks)
{
	int		n;
	int		philos;
	t_philo	*place;

	philos = common->n_philos;
	place = malloc(philos * sizeof(t_philo));
	if (place == NULL)
		return (NULL);
	n = 0;
	while (n < philos)
	{
		place[n].id = n + 1;
		place[n].meals = 0;
		place[n].last_meal = common->start_time;
		place[n].common = common;
		place[n].left_fork = *forks;
		place[n].right_fork = *forks;
		n++;
	}
	return (place);
}

void	sem_free(t_philo *philo)
{
	sem_clean();
	sem_close(philo->common->notify);
	sem_close(philo->common->eat);
	sem_close(philo->common->stop);
	sem_close(philo->common->forks);
	sem_close(philo->left_fork);
}

void	sem_clean(void)
{
	sem_unlink(SEM_NOTIFY);
	sem_unlink(SEM_LOG);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_FORKS);
}
