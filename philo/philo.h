/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:35:03 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/29 12:40:05 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>

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
	int		meals;
	t_mutex	work_mutex;
}	t_ctrl;

/* Convert a numeric string to an integer. */
int		to_int(const char *number);

/* Parse arguments. Return an array of integers on success, otherwise NULL. */
int		*parse(int argc, char **argv);

/* Initialize and populate the internal structure for control data. */
t_bool	init_control_data(int argc, char **argv);

/* Get address from control data structure. */
t_ctrl	*get_control_data(void);

#endif
