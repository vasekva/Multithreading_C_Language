/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:22:33 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/23 15:22:37 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_header.h"

static size_t	iteration(const char *str, int index, int neg)
{
	size_t	i;
	size_t	count;
	size_t	res;

	res = 0;
	count = 0;
	i = index;
	while (str[i] > 47 && str[i] < 58)
	{
		if (count > 20)
		{
			if (neg < 0)
				return (0);
			else
				return (-1);
		}
		res = res * 10 + str[i++] - '0';
		count++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;
	int	flag;

	flag = 0;
	i = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == 45 || str[i] == 43)
	{
		if (flag > 0)
			return (0);
		flag++;
		if (str[i] == 45)
			neg = -neg;
		i++;
	}
	res = iteration(str, i, neg);
	return (res * neg);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	size *= count;
	str = malloc(size);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, size);
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*p_dest;

	p_dest = destination;
	if (n != 0)
	{
		while (n-- != 0)
			*p_dest++ = (unsigned char)c;
	}
	return (destination);
}
