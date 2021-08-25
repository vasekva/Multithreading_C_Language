#include "tmp_header.h"

void    philo_eat(struct_philo *phi_str, t_philo *philo)
{
    long long i;

    pthread_mutex_lock(&(philo->forks[phi_str->left_fork_id]));
    display_out(philo, phi_str->philo_id, "has taken a fork");
    pthread_mutex_lock(&(philo->forks[phi_str->right_fork_id]));
	display_out(philo, phi_str->philo_id, "has taken a fork");
	pthread_mutex_lock(&(philo->mutex_meal));
	display_out(philo, phi_str->philo_id, "is eating");
	phi_str->last_meal = timestamp();
	pthread_mutex_unlock(&(philo->mutex_meal));
    i = timestamp();
	while (!(philo->died))
    {
		if (time_diff(i, timestamp()) >= philo->time_to_eat)
            break;
        usleep(50);
    }
	(phi_str->meal_count)++;
	pthread_mutex_unlock(&(philo->forks[phi_str->left_fork_id]));
	pthread_mutex_unlock(&(philo->forks[phi_str->right_fork_id]));
}

void    philo_sleep(t_philo *philo, struct_philo *p)
{
    long long i;

    display_out(philo, p->philo_id, "sleeping");
    i = timestamp();
    while (!(philo->died))
    {
        if (time_diff(i, timestamp()) >= philo->time_to_sleep)
            break;
        usleep(50);
    }
}

void    *life(void  *data)
{
    struct_philo    *phi_str;
    t_philo         *philo;

    phi_str = (struct_philo  *)data;
    philo = phi_str->t_philo;
    if (phi_str->philo_id % 2)
        usleep(15000);
    while (!(philo->died))
    {
        philo_eat(phi_str, philo);
        if (philo->is_all_ate)
            break;
        philo_sleep(philo, phi_str);
//        display_out(new_main_part, phi_str->philo_id, "eating");
    }
    return (NULL);
}