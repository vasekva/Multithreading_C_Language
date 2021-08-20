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

int	init_struct(t_params *params, int argc, char **argv)
{
	params->n_philo = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->must_eat = ft_atoi(argv[5]);
	else
		params->must_eat = -1;
	params->died = 0;
	params->all_ate = 0;
	return (0);
}

int main(int argc, char *argv[])
{
    t_params params;

    if (ft_check_params(argc, &argv[1]) == -1)
    	return (-1);
	init_struct(&params, argc, argv);
	if (init_all(&params))
    {
	ft_error(&params);
        return (1);
    }
    if (launch_program(&params))
    {
    	params.error = LAUNCH;
    	ft_error(&params);
        return (1);
    }
    return (0);
}