#include "main_header.h"

void	philo_isalive(t_philo *philo, int process_time)
{
	if (process_time >= philo->last_meal + philo->params->time_to_die)
	{
		philo->status = dead;
		print_message(philo); // <--
		philo->params->stop_flag = 1;
	}
}

int	print_message(t_philo *philo)
{
	if (philo->params->stop_flag == 1)
		return (0);
	if (pthread_mutex_lock(&philo->params->console) != 0)
		return (-1);
	printf("%d %d ", get_elapsed_time(philo->params->begin_time), philo->philo_id); // <--
	if (philo->status == thinking)
		printf("is thinking\n");
	if (philo->status == eating)
		printf("is eating\n");
	if (philo->status == sleeping)
		printf("is sleeping\n");
	if (philo->status == dead)
		printf("died\n");
	if (philo->status == taking_fork)
		printf("has taken a fork\n");
	if (pthread_mutex_unlock(&philo->params->console) != 0)
		return (-1);
	return (0);
}

int philo_endmeal(t_philo *philo, int process_time)
{
	if (pthread_mutex_unlock(&philo->params->forks[philo->left_fork_id]) != 0)
		return (-1);
	if (pthread_mutex_unlock(&philo->params->forks[philo->right_fork_id]) != 0)
		return (-1);
	if (philo->status == dead)
		return (0);
	philo->meal_count++;
	philo->status = sleeping;
	philo->sleep_start = process_time;
	if (philo->meal_count >= philo->params->meal_count)
	{
		pthread_mutex_lock(&philo->params->console);
		philo->params->num_of_philo_eaten++;
		pthread_mutex_unlock(&philo->params->console);
	}
	print_message(philo); // <--
	return (0);
}

int philo_startmeal(t_philo *philo, int process_time)
{
	if (pthread_mutex_lock(&philo->params->forks[philo->left_fork_id]) != 0)
		return (-1);
	philo->status = taking_fork;
	print_message(philo);
	if (pthread_mutex_lock(&philo->params->forks[philo->right_fork_id]) != 0)
		return (-1);
	philo->status = taking_fork;
	print_message(philo);
	process_time = get_elapsed_time(philo->params->begin_time); // <--
	philo_isalive(philo, process_time); // <--
	if (philo->status == dead)
		philo_endmeal(philo, process_time); // <--
	philo->status = eating;
	print_message(philo); // <--
	philo->last_meal = process_time;
	return (0);
}
