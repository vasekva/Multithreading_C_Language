#include "tmp_header.h"

void    check_if_death(t_philo *philo, struct_philo *phi)
{
    int i;

    while (!(philo->is_all_ate))
    {
        i = -1;
        while (++i < philo->num_of_philo && !(philo->died))
		{
			pthread_mutex_lock(&(philo->mutex_meal));
			if (time_diff(phi[i].last_meal, timestamp()) > philo->time_to_die)
			{
				display_out(philo, i, "died");
				philo->died = 1;
			}
			pthread_mutex_unlock(&(philo->mutex_meal));
			usleep(100);
		}
		if (philo->died)
			break ;
		i = 0;
		while (philo->must_eat != -1 && i < philo->num_of_philo && phi[i].meal_count >= philo->must_eat)
			i++;
		if (i == philo->num_of_philo)
			philo->is_all_ate = 1;
    }
}

void    join_destroy(t_philo *philo, struct_philo *phi)
{
    int i;

	i = -1;
	while (++i < philo->num_of_philo)
		pthread_join(phi[i].thread_id, NULL);
	i = -1;
	while (++i < philo->num_of_philo)
		pthread_mutex_destroy(&(philo->forks[i]));
	pthread_mutex_destroy(&(philo->console));
}

int     launch_program(t_philo *philo)
{
    int     i;
    struct_philo *phi;

    i = 0;
    phi = philo->philosophers;
    philo->begin_time = timestamp();
    while (i < philo->num_of_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, life, &(phi[i])))
        {
			return (1);
        }
		phi[i].last_meal = timestamp();
		i++;
	}
    check_if_death(philo, philo->philosophers);
    join_destroy(philo, phi);
    return (0);
}

int ft_alone(t_philo *philo)
{
	if (philo->num_of_philo == 1)
    {
        printf("0 1 has taken a fork\n");
        usleep(philo->time_to_die * 1000);
        printf("%d 1 is dead\n", philo->time_to_die);
        return (1);
    }
	return (0);
}

int	init_struct(t_philo *params, int argc, char **argv)
{
	params->num_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->must_eat = ft_atoi(argv[5]);
	else
		params->must_eat = -1;
	params->died = 0;
	params->is_all_ate = 0;
	return (0);
}

int    init_mutex(t_philo *philo)
{
	int i;

	i = philo->num_of_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(philo->forks[i]), NULL))
			return (-1);
	}
	if (pthread_mutex_init(&(philo->console), NULL))
		return (-1);
	if (pthread_mutex_init(&(philo->mutex_meal), NULL))
		return (-1);
	return (0);
}

void    get_philosophers(t_philo *philo)
{
	int i;

	i = philo->num_of_philo;
	while (--i >= 0)
	{
		philo->philosophers[i].philo_id = i;
		philo->philosophers[i].meal_count = 0;
		philo->philosophers[i].left_fork_id = i;
		philo->philosophers[i].right_fork_id = (i + 1) % philo->num_of_philo;
		philo->philosophers[i].last_meal = 0;
		philo->philosophers[i].t_philo = philo;
	}
}

int main(int argc, char *argv[])
{
    t_philo params;

    if (ft_check_params(argc, &argv[1]) == -1)
    	return (-1);
    init_struct(&params, argc, argv);
	if (init_mutex(&params) == -1)
    {
		exception(SIX);
        return (1);
    }
	if (ft_alone(&params))
        return (1);
	get_philosophers(&params);
	if (launch_program(&params))
    {
		exception(SEVEN);
        return (1);
    }
    return (0);
}