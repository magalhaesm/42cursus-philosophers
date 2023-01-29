/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:35:03 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/29 16:47:52 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef struct s_ctrl {
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	t_mutex	work_mutex;
}	t_ctrl;

typedef struct s_fork {
	t_bool	in_use;
	t_mutex	mutex;
}	t_fork;

typedef struct s_philo {
	int		id;
	t_fork	*left_fork;
	t_fork	*right_fork;
}	t_philo;

/* Convert a numeric string to an integer. */
int		to_int(const char *number);

/* Parse arguments. Return an array of integers on success, otherwise NULL. */
int		*parse(int argc, char **argv);

/* Parse input and populate common data structure. */
t_bool	init_common_data(int argc, char **argv);

/* Get address from control data structure. */
t_ctrl	*get_common_data(void);

/* Get the total number of philosophers. */
int		get_number_of_philos(void);

/* Create and initialize a mutex per fork. Return an array of forks on success,
 * and NULL on error. */
t_fork	**arrange_forks(int philos);

/* Check if a fork is available for use. */
t_bool	fork_available(t_fork *fork);

/* Take the left and right forks and make them unavailable to any
 * other philosopher. */
void	take_forks(t_philo *philo);

/* Drop left and right forks and make them available to other philosophers. */
void	put_forks(t_philo *philo);

/* Deallocate memory from array of forks. */
void	free_forks(t_fork **forks);

/* Represent a philosopher who eats, thinks, sleeps and dies of starvation. */
void	*philosopher(void *arg);

#endif
