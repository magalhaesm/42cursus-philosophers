/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:23:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/01 13:11:39 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define FORK "%05ld %d has taken a fork\n"
#define EAT "%05ld %d is eating\n"
#define SLEEP "%05ld %d is sleeping\n"
#define THINK "%05ld %d is thinking\n"

long	get_elapsed_time(long start);

void	log_state(t_state state, t_philo *philo)
{
	int		id;
	long	start;
	long	elapsed;
	char	*message;

	id = philo->id;
	start = get_common_data()->start_time;
	elapsed = get_elapsed_time(start);
	if (state == EATING)
	{
		message = FORK FORK EAT;
		printf(message, elapsed, id, elapsed, id, elapsed, id);
	}
	else if (state == SLEEPING)
	{
		message = SLEEP;
		printf(message, elapsed, id);
	}
	else if (state == THINKING)
	{
		message = THINK;
		printf(message, elapsed, id);
	}
}

long	get_current_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

long	get_elapsed_time(long start)
{
	long int	ms_now;

	ms_now = get_current_time();
	return (ms_now - start);
}
