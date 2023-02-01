/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:37:04 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/31 15:33:22 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->in_use = TRUE;
	pthread_mutex_unlock(&fork->mutex);
}

void	unlock(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->in_use = FALSE;
	pthread_mutex_unlock(&fork->mutex);
}

t_bool	is_locked(t_fork *fork)
{
	t_bool	locked;

	locked = FALSE;
	pthread_mutex_lock(&fork->mutex);
	if (fork->in_use)
		locked = TRUE;
	pthread_mutex_unlock(&fork->mutex);
	return (locked);
}
