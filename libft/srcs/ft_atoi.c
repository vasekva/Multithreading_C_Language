#include "libft.h"

static size_t	iteration(const char *str, int index, int neg)
{
	size_t i;
	size_t count;
	size_t res;

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
	int neg;
	int res;
	int flag;

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