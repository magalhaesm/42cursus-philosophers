/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:23:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/31 21:04:59 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_itoa(long n);
size_t	ft_strlen(const char *s);
long	get_elapsed_time(long start);
void	bufwrite(char *elapsed, char *id, char *msg, char *buffer);

void	log_state(t_state state, t_philo *philo)
{
	char	*nbr;
	long	start;
	char	*elapsed;
	char	buffer[BUFSIZE];

	memset(buffer, 0, BUFSIZE);
	nbr = ft_itoa(philo->id);
	start = get_common_data()->start_time;
	elapsed = ft_itoa(get_elapsed_time(start));
	if (state == EATING)
	{
		bufwrite(elapsed, nbr, " has taken a fork\n", buffer);
		bufwrite(elapsed, nbr, " has taken a fork\n", buffer);
		bufwrite(elapsed, nbr, " is eating\n", buffer);
	}
	write(STDOUT_FILENO, buffer, ft_strlen(buffer));
	free(nbr);
	free(elapsed);
}

long	get_current_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
}

long	get_elapsed_time(long start)
{
	long int	ms_now;

	ms_now = get_current_time();
	return (ms_now - start);
}
