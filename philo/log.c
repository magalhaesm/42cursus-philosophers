/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:23:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/31 21:24:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_itoa(long n);
long	get_elapsed_time(long start);
void	bufwrite(char *elapsed, char *id, char *msg, char *buffer);

void	log_state(t_state state, t_philo *philo)
{
	char	*id;
	long	start;
	char	*elapsed;
	char	buffer[BUFSIZE];

	memset(buffer, 0, BUFSIZE);
	id = ft_itoa(philo->id);
	start = get_common_data()->start_time;
	elapsed = ft_itoa(get_elapsed_time(start));
	if (state == EATING)
	{
		bufwrite(elapsed, id, " has taken a fork\n", buffer);
		bufwrite(elapsed, id, " has taken a fork\n", buffer);
		bufwrite(elapsed, id, " is eating\n", buffer);
	}
	else if (state == SLEEPING)
		bufwrite(elapsed, id, " is sleeping\n", buffer);
	else if (state == THINKING)
		bufwrite(elapsed, id, " is thinking\n", buffer);
	write(STDOUT_FILENO, buffer, ft_strlen(buffer));
	free(elapsed);
	free(id);
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
