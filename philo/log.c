/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:23:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/02 08:48:04 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define FORK "%05ld %d has taken a fork\n"
#define EATING "%05ld %d is eating\n"
#define SLEEPING "%05ld %d is sleeping\n"
#define THINKING "%05ld %d is thinking\n"
#define DEAD "%05ld %d died\n"

long	log_state(t_state state, t_philo *philo)
{
	int		id;
	long	start;
	long	elapsed;

	id = philo->id;
	start = philo->common->start_time;
	elapsed = get_elapsed_time(start);
	pthread_mutex_lock(&philo->common->log);
	if (state == EAT)
		printf(FORK FORK EATING, elapsed, id, elapsed, id, elapsed, id);
	else if (state == SLEEP)
		printf(SLEEPING, elapsed, id);
	else if (state == THINK)
		printf(THINKING, elapsed, id);
	else if (state == DEATH)
		printf(DEAD, elapsed, id);
	pthread_mutex_unlock(&philo->common->log);
	return (elapsed);
}

long	get_current_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

long	get_elapsed_time(long start)
{
	return (get_current_time() - start);
}
