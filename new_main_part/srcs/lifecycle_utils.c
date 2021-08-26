#include "tmp_header.h"

void	free_clean(t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&philo->dead_philo);
	pthread_mutex_destroy(&philo->message);
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->dead_philo);
	free(philo->forks);
	free(philo->s_params);
}

int	ft_digits(char *str)
{
	int	f;
	int	i;

	f = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			f = 1;
		i++;
	}
	return (f);
}

long	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
}
