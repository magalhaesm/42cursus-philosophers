/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:47:19 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/02/08 11:47:23 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define CONVERTION_ERROR -1

static int	ft_isdigit(int c);
static int	*parse_int(int argc, char **argv);

int	*parse(int argc, char **argv)
{
	int	*numbers;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid arguments\n");
		return (NULL);
	}
	numbers = parse_int(argc, argv);
	if (numbers == NULL)
		printf("Invalid arguments\n");
	return (numbers);
}

int	to_int(const char *number)
{
	int	digit;
	int	integer;

	digit = 0;
	integer = 0;
	if (number[digit] == 0)
		return (CONVERTION_ERROR);
	while (number[digit])
	{
		if (ft_isdigit(number[digit]))
		{
			integer = number[digit] - '0' + (integer * 10);
			digit++;
		}
		else
			return (CONVERTION_ERROR);
	}
	return (integer);
}

static int	*parse_int(int argc, char **argv)
{
	int	arg;
	int	*numbers;

	arg = 1;
	numbers = malloc(sizeof(int) * argc - 1);
	while (argv[arg])
	{
		numbers[arg - 1] = to_int(argv[arg]);
		if (numbers[arg - 1] == CONVERTION_ERROR)
		{
			free(numbers);
			return (NULL);
		}
		arg++;
	}
	return (numbers);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
