/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 09:42:26 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/29 10:27:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c);

#define CONVERTION_ERROR -1

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

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
