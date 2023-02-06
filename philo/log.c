/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:23:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/06 11:18:11 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define FORK "%5ld  %d has taken a fork\n"
#define EATING "%5ld  %d is eating\n"
#define SLEEPING "%5ld  %d is sleeping\n"
#define THINKING "%5ld  %d is thinking\n"
#define DEAD "%5ld  %d died\n"

long	state_log(t_state state, t_philo *philo)
{
	int		id;
	long	start;
	long	current;
	long	elapsed;

	id = philo->id;
	start = philo->common->start_time;
	pthread_mutex_lock(&philo->common->log);
	current = get_current_time();
	elapsed = current - start;
	if (state == EAT)
		printf(FORK FORK EATING, elapsed, id, elapsed, id, elapsed, id);
	else if (state == ALONE)
		printf(FORK, elapsed, id);
	else if (state == SLEEP)
		printf(SLEEPING, elapsed, id);
	else if (state == THINK)
		printf(THINKING, elapsed, id);
	else if (state == DEATH)
		printf(DEAD, elapsed, id);
	pthread_mutex_unlock(&philo->common->log);
	return (current);
}

long	get_current_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
