/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:44:10 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/20 11:25:57 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>

# define SEM_FORKS "/sem_forks"

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
	size_t	start_time;
	int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat;
	sem_t	*notify;
	sem_t	*log;
	sem_t	*eat;
	sem_t	*forks;
	sem_t	*stop;
}	t_ctrl;

typedef struct s_philo {
	int			id;
	pid_t		pid;
	pthread_t	tid;
	int			meals;
	size_t		last_meal;
	t_ctrl		*common;
	sem_t		*left_fork;
	sem_t		*right_fork;
}	t_philo;

int		*parse(int argc, char **argv);
size_t	get_current_time(void);
t_bool	init_common_data(int argc, char **argv, t_ctrl *common);
sem_t	*init_forks(t_ctrl *common);
void	sem_free(t_philo *philo);
t_philo	*init_philosophers(t_ctrl *common, sem_t **forks);
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
t_bool	stop_dinner(t_philo *philo);
size_t	state_log(t_state state, t_philo *philo);
void	*stop_monitor(void *arg);
void	mssleep(size_t ms_time);

#endif
