/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:22:40 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/23 15:22:42 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_header.h"

static char	*rev_print(char *str)
{
	int		i;
	int		length;
	char	buff;

	i = 0;
	length = ft_strlen(str);
	while (length - 1 > i)
	{
		buff = str[i];
		str[i] = str[length - 1];
		str[length - 1] = buff;
		length--;
		i++;
	}
	return (str);
}

static size_t	is_neg(int n)
{
	if (n < 0)
		return (n *= -1);
	else
		return (n);
}

static size_t	ft_numsize(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (2);
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	if (size > 10)
		size = 10;
	return (size + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		neg;
	size_t	size;

	size = ft_numsize(n);
	neg = (n < 0);
	str = ft_calloc(size + neg, sizeof(*str));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	len = 0;
	while (n != 0)
	{
		str[len++] = is_neg(n % 10) + '0';
		n /= 10;
	}
	if (neg)
		str[len] = '-';
	str = rev_print(str);
	return (str);
}

int	exception(char *str)
{
	int	i;

	i = 0;
	write(1, "Error: ", 7);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (-1);
}
