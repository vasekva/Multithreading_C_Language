#include "main_header.h"

int clear_all(t_params *args)
{
	int	i;

	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	i = 0;
	while (i < args->num_of_philo)
	{
		if (pthread_detach(args->philos[i]) != 0)
			return (-1);
		i++;
	}
	free(args->philos);
	free(args->forks);
	free(args->philo_data);
	return (0);
}

int run_observe_philo(t_params *params)
{
	int process_time;
	int i;

	while (params->stop_flag == 0)
	{
		if (params->meal_count != 0 && (params->num_of_philo_eaten >= params->num_of_philo))
		{
			params->stop_flag = 1;
			break ;
		}
		i = 0;
		while (i < params->num_of_philo)
		{
			process_time = get_time(params->begin_time);
			if (process_time == -1)
				return (-1);
			if (process_time >= params->philo_data[i]->last_meal + params->time_to_die)
			{
				params->philo_data[i]->status = dead;
				print_message(params->philo_data[i]);
				params->philo_data[i]->params->stop_flag = 1;
			}
			i++;
		}
		usleep(1);
	}
	return (0);
}

int	init_struct(t_params *params, int argc, char **argv)
{
	params->num_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->meal_count = ft_atoi(argv[5]);
	else
		params->meal_count = 0;
	params->stop_flag = 0;
	params->num_of_philo_eaten = 0; // -1
	params->philo_data = malloc(sizeof(t_philo *) * params->num_of_philo);
	params->philos = malloc(sizeof(pthread_t) * params->num_of_philo);
	params->forks = malloc(sizeof(pthread_mutex_t) * params->num_of_philo);
	if (!params->philos || !params->forks || !params->philo_data)
		return (-1);
	else
		return (0);
}

int	main(int argc, char *argv[])
{
	t_params params;
	int i;

	if (ft_check_params(argc, &argv[1]) == -1)
		return (-1);
	if (init_struct(&params, argc, argv) == -1)
		return (-1);
	i = 0;
	gettimeofday(&params.begin_time, NULL);
	while (i < params.num_of_philo)
	{
		pthread_mutex_init(&params.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&params.console, NULL);
	run_lifecycle(&params);
	run_observe_philo(&params);
	clear_all(&params);
	return (0);
}
