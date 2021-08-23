#include "bonus_header.h"

void    close_lifecycle(t_params *params)
{
	int i;
	int ret;

	i = -1;
	while (++i < params->num_of_philo)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < params->num_of_philo)
				kill(params->philosophers[i].process_id, SIGTERM);
			break ;
		}
	}
	sem_close(params->forks);
	sem_close(params->console);
	sem_close(params->meal);
}

int     init_other(t_params *params)
{
    int i;

    i = -1;
    while (++i < params->num_of_philo)
    {
		params->philosophers[i].philo_id = i;
		params->philosophers[i].last_meal = 0;
		params->philosophers[i].process_id = 0;
        params->philosophers[i].meal_count = 0;
		params->philosophers[i].t_philo = params;
		params->philosophers[i].thread_id = NULL;
    }
    sem_unlink("forks");
    sem_unlink("console");
    sem_unlink("meal");
    params->forks = sem_open("forks", O_CREAT, S_IRWXU, params->num_of_philo);
    params->console = sem_open("console", O_CREAT, S_IRWXU, 1);
    params->meal = sem_open("meal", O_CREAT, S_IRWXU, 1);
    return (0);
}

int	init_dataset(t_params *params, int argc, char **argv)
{
	params->num_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->meal_count = ft_atoi(argv[5]);
	else
		params->meal_count = -1;
	params->died = 0;
	params->all_ate = 0;
	init_other(params);
	return (0);
}

int main(int argc, char *argv[])
{
    t_params params;

    if (ft_check_params(argc, &argv[1]) == -1)
    	return (-1);
    init_dataset(&params, argc, argv);
    if (start_lifecycle(&params))
    {
		exception(SIX);
        return (1);
    }
    close_lifecycle(&params);
    return (0);
}