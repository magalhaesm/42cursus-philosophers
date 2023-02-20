/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:55:26 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/20 10:30:57 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define FORK "%5ld %2d has taken a fork\n"
#define EAT "%5ld %2d is eating\n"
#define SLEEP "%5ld %2d is sleeping\n"
#define THINK "%5ld %2d is thinking\n"
#define DEATH "%5ld %2d died\n"

size_t	state_log(t_state state, t_philo *philo)
{
	int		id;
	size_t	current;
	size_t	elapsed;

	id = philo->id;
	sem_wait(philo->common->log);
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
	sem_post(philo->common->log);
	return (current);
}

long	get_current_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}
