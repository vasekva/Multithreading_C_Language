#include "tmp_header.h"

void	*live(void *tmp)
{
	pthread_t	tred;
	t_params		*s_params;

	s_params = (t_params *)tmp;
	if (s_params->even)
	{
		usleep(1000);
		s_params->even = 0;
	}
	s_params->last_eat = get_time();
	s_params->time_to_death = s_params->last_eat + s_params->all->time_to_die;
	if (pthread_create(&tred, NULL, &checkers, s_params) != 0)
		return ((void *)1);
	pthread_detach(tred);
	while (s_params->eaten != s_params->all->meal_count)
		loop_live(s_params);
	usleep(1000);
	pthread_mutex_lock(&s_params->all->message);
	pthread_mutex_unlock(&s_params->all->dead_philo);
	return (NULL);
}

void	*check_live(void *tmp)
{
	t_philo	*philo;
	int			i;

	philo = (t_philo *)tmp;
	while (1)
	{
		i = 0;
		while (i < philo->num_of_philo)
		{
			if (philo->s_params[i].eaten < philo->meal_count)
				break ;
			i++;
		}
		if (i == philo->num_of_philo)
			break ;
		usleep(1000);
	}
	pthread_mutex_lock(&philo->message);
	pthread_mutex_unlock(&philo->dead_philo);
	return (NULL);
}

int	start_pthread(t_philo *philo)
{
	int			i;
	pthread_t	tred;

	philo->start = get_time();
	if (philo->meal_count != -1)
	{
		if (pthread_create(&tred, NULL, &check_live, philo) != 0)
			return (1);
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->s_params[i].time_to_death = get_time() + philo->time_to_die;
		if (pthread_create(&philo->s_params[i].thread, NULL, &live,
						   (void *)(&philo->s_params[i])) != 0)
			return (-1);
		pthread_detach(philo->s_params[i].thread);
		i++;
	}
	return (0);
}

void	make_start(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->message, NULL);
	pthread_mutex_init(&philo->dead_philo, NULL);
	pthread_mutex_lock(&philo->dead_philo);
}

void	start_game(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->s_params[i].last_eat = 0;
		philo->s_params[i].how_dead = 0;
		philo->s_params[i].eaten = 0;
		philo->s_params[i].nbr = i + 1;
		philo->s_params[i].even = 0;
		if ((philo->s_params[i].nbr % 2) == 0)
			philo->s_params[i].even = 1;
		philo->s_params[i].left_fork = &philo->forks[i];
		philo->s_params[i].right_fork = &philo->forks[(i + 1) % philo->num_of_philo];
		philo->s_params[i].all = philo;
		i++;
	}
	make_start(philo);
	start_pthread(philo);
}
