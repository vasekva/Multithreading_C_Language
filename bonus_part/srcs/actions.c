#include "bonus_header.h"

void	check_philo(t_philo *philo, int process_time)
{
	if (process_time >= philo->last_meal + philo->params->time_to_die)
	{
		philo->status = dead;
		print_message(philo);
		philo->params->stop_flag = 1;
	}
}

int	print_message(t_philo *philo)
{
	char	*str;

	if (philo->params->stop_flag == 1)
		return (0);
	sem_wait(philo->params->sem_console);
	str = ft_itoa(get_time(philo->params->begin_time));
	write(1, str, ft_strlen(str));
	free(str);
	write(1, " #", 2);
	str = ft_itoa(philo->philo_id);
	write(1, str, ft_strlen(str));
	free(str);
	write(1, " ", 1);
	if (philo->status == thinking)
		write(1, "is thinking\n", 12);
	if (philo->status == eating)
		write(1, "is eating\n", 10);
	if (philo->status == sleeping)
		write(1, "is sleeping\n", 12);
	if (philo->status == dead)
		write(1, "died\n", 5);
	if (philo->status == taking_fork)
		write(1, "has taken a fork\n", 17);
	sem_post(philo->params->sem_console);
	return (0);
}

int	finish_meal(t_philo *philo, int process_time)
{
	sem_post(philo->params->sem_forks);
	sem_post(philo->params->sem_forks);
	if (philo->status == dead)
		return (0);
	philo->meal_count++;
	philo->status = sleeping;
	philo->sleep_start = process_time;
	if (philo->meal_count >= philo->params->meal_count)
	{
		philo->params->num_of_philo_eaten++;
	}
	print_message(philo);
	return (0);
}

int	start_meal(t_philo *philo, int process_time)
{
	sem_wait(philo->params->sem_forks);
	philo->status = taking_fork;
	print_message(philo);
	sem_wait(philo->params->sem_forks);
	philo->status = taking_fork;
	print_message(philo);
	process_time = get_time(philo->params->begin_time);
	check_philo(philo, process_time);
	if (philo->status == dead)
		finish_meal(philo, process_time);
	philo->status = eating;
	print_message(philo);
	philo->last_meal = process_time;
	return (0);
}
