#include "bonus_header.h"

int     init_all(t_params *params)
{
    int i;

    i = params->n_philo;
    while (--i >= 0)
    {
        params->philosophers[i].meal_count = 0;
		params->philosophers[i].last_meal = 0;
		params->philosophers[i].t_philo = params;
		params->philosophers[i].philo_id = i;
    }
    sem_unlink("/forks");
    sem_unlink("/display");
    sem_unlink("/check_meal");
    params->forks = sem_open("/forks", O_CREAT, S_IRWXU, params->n_philo);
    params->console = sem_open("/display", O_CREAT, S_IRWXU, 1);
    params->check_meal = sem_open("/check_meal", O_CREAT, S_IRWXU, 1);
    return (0);
}

int main(int argc, char *argv[])
{
    t_params philo;

    if (ft_check_params(argc, &argv[1]) == -1)
    	return (-1);
    if (get_arg(&philo, argc, argv) != 0)
    {
        ft_error(&philo);
        return (1);
    }
    if (init_all(&philo))
    {
        ft_error(&philo);
        return (1);
    }
    if (launch_program(&philo))
    {
        philo.error = LAUNCH;
        ft_error(&philo);
        return (1);
    }
    return (0);
}