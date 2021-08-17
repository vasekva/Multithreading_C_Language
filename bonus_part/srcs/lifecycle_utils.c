#include "bonus_header.h"

int	get_time(struct timeval start)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	return (((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((start.tv_sec * 1000) + (start.tv_usec / 1000)));
}

int	check_status(t_philo *philo, int process_time)
{
	if (process_time == -1)
		return (-1);
	check_philo(philo, process_time);
	if (philo->params->stop_flag == 1)
		return (-1);
	if (philo->status == thinking)
	{
		start_meal(philo, process_time);
	}
	if (philo->status == eating)
	{
		if (process_time >= philo->last_meal + philo->params->time_to_eat)
			finish_meal(philo, process_time);
	}
	if (philo->status == sleeping)
	{
		if (process_time >= philo->sleep_start
			+ philo->params->time_to_sleep)
		{
			philo->status = thinking;
			print_message(philo);
		}
	}
	return (0);
}

void	*start_processes(void *data)
{
	t_philo	*philo;
	int		process_time;

	philo = (t_philo *)data;
	printf("ID: %d PID: %d\n", philo->philo_id, philo->philo_pid);
	return (NULL);
	while (philo->params->stop_flag == 0)
	{
		process_time = get_time(philo->params->begin_time);
		if (check_status(philo, process_time) == -1)
			return (NULL);
		usleep(1);
	}
	free(data);
	return (NULL);
}

int	 run_lifecycle(t_params *params)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < params->num_of_philo)
	{
		philo = malloc(sizeof(t_philo));
//		philo->philo_id = i + 1;
		philo->philo_pid = 0;
		philo->params = params;
		philo->status = thinking;
		philo->last_meal = 0;
		philo->meal_count = 0;
		philo->sleep_start = 0;
		params->philo_data[i] = philo;
//		pthread_create(&params->philos[i], NULL, start_processes, philo);
		usleep(100);
	}
	i = -1;
//	philo->philo_pid = fork();
	while (++i < params->num_of_philo)
	{
		if (philo->philo_pid == 0)
		{
			if (i + 1 != params->num_of_philo)
				philo->philo_pid = fork();
			philo->philo_id = i + 1;
		}
	}
	start_processes(philo);
	return (0);
}
