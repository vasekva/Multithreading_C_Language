#include "main_header.h"

void	check_philo(t_philo *philo, int process_time)
{
	if (process_time >= philo->last_meal + philo->params->time_to_die)
	{
		philo->status = dead;
		print_message(philo);
		philo->params->stop_flag = 1;
	}
}

static void	print_num_str(int number)
{
	char	*tmp;

	tmp = ft_itoa(number);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
}

int	print_message(t_philo *philo)
{
	if (philo->params->stop_flag == 1)
		return (0);
	pthread_mutex_lock(&philo->params->console);
	print_num_str(get_time(philo->params->begin_time));
	write(1, " #", 2);
	print_num_str(philo->philo_id);
	write(1, " ", 1);
	if (philo->status == thinking)
		write(1, "is thinking\n", 12);
	if (philo->status == eating)
		write(1, "is eating\n", 10);
	if (philo->status == sleeping)
		write(1, "is sleeping\n", 12);
	if (philo->status == dead)
		write(1, "died\n", 5);
	if (philo->status == taking_l_fork)
		write(1, "get left fork\n", 14);
	if (philo->status == taking_r_fork)
		write(1, "get right fork\n", 15);
	pthread_mutex_unlock(&philo->params->console);
	return (0);
}

int	finish_meal(t_philo *philo, int process_time)
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
		philo->params->num_of_philo_eaten++;
	}
	print_message(philo);
	return (0);
}

int	start_meal(t_philo *philo, int process_time)
{
	if (pthread_mutex_lock(&philo->params->forks[philo->left_fork_id]) != 0)
		return (-1);
	philo->status = taking_l_fork;
	print_message(philo);
	if (pthread_mutex_lock(&philo->params->forks[philo->right_fork_id]) != 0)
		return (-1);
	philo->status = taking_r_fork;
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
