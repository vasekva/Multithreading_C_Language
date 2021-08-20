#include "bonus_header.h"

void    philo_eat(t_philo *philo, t_params *params)
{
    long long t;
    sem_wait(params->forks);
    display_out(params, philo->philo_id, "get left fork");
    sem_wait(params->forks);
    display_out(params, philo->philo_id, "get right fork");
    sem_wait(params->check_meal);
    display_out(params, philo->philo_id, "is eating");
    sem_post(params->check_meal);
    t = timestamp();
    while (params->died == 0)
    {
        if (time_diff(t, timestamp()) >= params->time_eat)
            break;
        usleep(50);
    }
    philo->meal_count++;
    sem_post(params->forks);
    philo->last_meal = timestamp();
    sem_post(params->forks);
}

void    *check_death(void   *philosopher)
{
    t_philo *phi_str;
    t_params *params;

    phi_str = (t_philo*)philosopher;
    params = phi_str->t_philo;
    while (1)
    {
        sem_wait(params->check_meal);
        if (time_diff(phi_str->last_meal, timestamp()) > params->time_die)
        {
        	display_out(params, phi_str->philo_id, "is died");
            params->died = 1;
            sem_wait(params->console);
            exit(1);
        }
        sem_post(params->check_meal);
        if (params->must_eat != -1 && phi_str->meal_count >= params->must_eat)
        {
            params->all_ate = 1;
            break;
        }
        usleep(1000);
    }
    exit(0);
    return (NULL);
}

void    philo_sleep(t_philo *philo, t_params *params)
{
	long long i;

	display_out(params, philo->philo_id, "is sleeping");
	i = timestamp();
	while (!(params->died))
	{
		if (time_diff(i, timestamp()) >= params->time_sleep)
			break;
		usleep(50);
	}
}

void    start_processes(void *data, t_params *params)
{
    t_philo *philo;

    philo = (t_philo*)data;
    philo->last_meal = timestamp();
	pthread_create(&(philo->thread_id), NULL, check_death, data);
	if (philo->philo_id % 2) {
		usleep(15000);
	}

	while (params->died == 0 && params->all_ate != 1)
    {
        philo_eat(philo, params);
        if (philo->meal_count >= params->must_eat && params->must_eat != -1)
            break;
        display_out(params, philo->philo_id, "is sleeping");
        philo_sleep(philo, params);
        display_out(params, philo->philo_id, "is thinking");
    }
    pthread_join(philo->thread_id, NULL);
    if (params->died)
		exit(1);
	exit(0);
}

int     start_lifecycle(t_params *params)
{
    t_philo *philo;
    int         i;

    i = -1;
    philo = params->philosophers;
    params->start_time = timestamp();
    while (++i < params->num_of_philo)
    {
    	philo[i].process_id = fork();
    	if (philo[i].process_id < 0)
            return (1);
    	if (philo[i].process_id == 0)
        	start_processes(&(philo[i]), params);
        usleep(100);
    }
    return (0);
}