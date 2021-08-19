#include "bonus_header.h"

int			ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

void    display_out(t_params *params, int id, char *str)
{
    sem_wait(params->console);
	if (params->died == 0)
	{
		printf("%lli ", timestamp() - params->start_time);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	sem_post(params->console);
    return ;
}

long long time_diff(long long past, long long pres)
{
    return (pres - past);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void    ft_error(t_params *params)
{
    if (params->error == ARG_NUM)
    	write(2, "Error: Wrong number of arg\n", 28);
    if (params->error == ARG_NOT_NUM)
    	write(2, "Error: arg not number\n", 23);
    if (params->error == MUST_EAT)
    	write(2, "Error: number to must eat wrong\n",33);
    if (params->error == PHILO_NUM)
    	write(2, "Error: wrong number of philosophers\n",37);
    if (params->error == MUTEX)
    	write (2, "Error: MUTEX\n", 14);
    if (params->error == LAUNCH)
    	write(2, "Error: to launch program\n", 26);
    if (params->error == INIT)
    	write(2, "Error: initialization\n", 23);
}


