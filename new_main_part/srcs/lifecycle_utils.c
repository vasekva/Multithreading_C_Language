#include "tmp_header.h"

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

void    display_out(t_philo *philo, int id, char *str)
{
	pthread_mutex_lock(&(philo->console));
	if (!(philo->died))
	{
		printf("%lli ", timestamp() - philo->begin_time);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(philo->console));
    return ;
}
