/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:14 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/31 20:41:27 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	digits(unsigned int n);
char	*ft_itoa(long n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);

void	bufwrite(char *elapsed, char *id, char *msg, char *buffer)
{
	int	padding;

	padding = 5 - ft_strlen(elapsed);
	if (padding > 0)
		memset(buffer + ft_strlen(buffer), '0', padding);
	ft_strlcat(buffer, elapsed, BUFSIZE);
	ft_strlcat(buffer, " ", BUFSIZE);
	ft_strlcat(buffer, id, BUFSIZE);
	ft_strlcat(buffer, msg, BUFSIZE);
}

char	*ft_itoa(long n)
{
	char			*str;
	int				len;
	int				negative;
	unsigned long	nb;

	nb = n;
	negative = (n < 0);
	if (negative)
		nb = n * (-1);
	len = digits(nb) + negative;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}

int	digits(unsigned int n)
{
	if (n < 10)
		return (1);
	return (digits(n / 10) + 1);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (size <= dstlen)
		return (srclen + size);
	if (size)
	{
		while (dstlen < size - 1 && src[i])
		{
			dst[dstlen] = src[i];
			dstlen++;
			i++;
		}
		dst[dstlen] = '\0';
	}
	return (srclen + dstlen);
}

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}
