/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:06:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/29 10:45:35 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int	number;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid arguments\n");
		return (EXIT_FAILURE);
	}
	argv++;
	while (*argv)
	{
		number = to_int(*argv);
		if (number < 0)
			return (EXIT_FAILURE);
		printf("integer: %d from %s\n", number, *argv);
		argv++;
	}
	return (EXIT_SUCCESS);
}
