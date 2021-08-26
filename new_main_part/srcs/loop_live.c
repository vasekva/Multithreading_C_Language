#include "tmp_header.h"

void	message(char *str, t_params *s_params)
{
	pthread_mutex_lock(&s_params->all->message);
	printf("%ld %d %s\n", get_time() - s_params->all->start, s_params->nbr, str);
	pthread_mutex_unlock(&s_params->all->message);
}

void	loop_live(void *tmp)
{
	t_params	*s_params;

	s_params = (t_params *)tmp;
	pthread_mutex_lock(s_params->left_fork);
	message("has taken a left fork", tmp);
	pthread_mutex_lock(s_params->right_fork);
	message("has taken a right fork", tmp);
	message("is eating", tmp);
	usleep(s_params->all->time_to_eat * 1000);
	pthread_mutex_unlock(s_params->right_fork);
	pthread_mutex_unlock(s_params->left_fork);
	s_params->eaten += 1;
	s_params->time_to_death = get_time() + s_params->all->time_to_die;
	message("is sleeping", tmp);
	usleep(s_params->all->time_to_sleep * 1000);
	message("is thinking", tmp);
}

void	*checkers(void *tmp)
{
	t_params	*s_params;

	s_params = (t_params *)tmp;
	while (1)
	{
		pthread_mutex_lock(&s_params->check);
		if (get_time() > s_params->time_to_death)
		{
			pthread_mutex_lock(&s_params->all->message);
			printf("%ld %d died\n", get_time() - s_params->all->start, s_params->nbr);
			pthread_mutex_unlock(&s_params->check);
			pthread_mutex_unlock(&s_params->all->dead_philo);
			return (NULL);
		}
		pthread_mutex_unlock(&s_params->check);
		usleep(1000);
	}
}
