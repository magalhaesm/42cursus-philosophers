/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:35:03 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/06 14:15:01 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define DELAY 10

typedef pthread_mutex_t	t_mutex;

typedef enum e_state {
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;

typedef enum e_bool {
	FALSE,
	TRUE
}	t_bool;

typedef struct s_ctrl {
	long	start_time;
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	int		stuffed;
	t_bool	death;
	t_mutex	notify;
	t_mutex	log;
	t_mutex	eat;
	t_mutex	full;
}	t_ctrl;

typedef struct s_fork {
	t_mutex	mutex;
}	t_fork;

typedef struct s_philo {
	int		id;
	int		meals;
	long	last_meal;
	t_fork	*first_fork;
	t_fork	*second_fork;
	t_ctrl	*common;
}	t_philo;

/* Convert a numeric string to an integer. */
int		to_int(const char *number);

/* Parse arguments. Return an array of integers on success, otherwise NULL. */
int		*parse(int argc, char **argv);

/* Parse input and populate common data structure. */
t_bool	init_common_data(int argc, char **argv, t_ctrl *common);

/* Create and initialize a mutex per fork. Return an array of forks on success,
 * and NULL on error. */
t_fork	**init_forks(int philos);

/* Deallocate memory from array of forks. */
void	free_forks(t_fork **forks);

t_philo	*init_philosophers(t_ctrl *common, t_fork **forks);
t_bool	eating(t_philo *philo);
t_bool	thinking(t_philo *philo);
t_bool	sleeping(t_philo *philo);
long	state_log(t_state state, t_philo *philo);
long	get_current_time(void);
t_bool	check_dead(t_philo *philo);
void	*stop_monitor(void *arg);
int		mssleep(long ms);
int		min(int a, int b);
int		max(int a, int b);

#endif
