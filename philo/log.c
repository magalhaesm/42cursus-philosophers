/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:23:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/17 14:01:17 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define FORK "%5ld %2d has taken a fork\n"
#define EAT "%5ld %2d is eating\n"
#define SLEEP "%5ld %2d is sleeping\n"
#define THINK "%5ld %2d is thinking\n"
#define DEATH "%5ld %2d died\n"

long	state_log(t_state state, t_philo *philo)
{
	int		id;
	long	current;
	long	elapsed;

	id = philo->id;
	pthread_mutex_lock(&philo->common->log);
	current = get_current_time();
	elapsed = current - philo->common->start_time;
	if (state == EATING)
		printf(FORK FORK EAT, elapsed, id, elapsed, id, elapsed, id);
	else if (state == TAKE_FORK)
		printf(FORK, elapsed, id);
	else if (state == SLEEPING)
		printf(SLEEP, elapsed, id);
	else if (state == THINKING)
		printf(THINK, elapsed, id);
	else if (state == DEAD)
		printf(DEATH, elapsed, id);
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
