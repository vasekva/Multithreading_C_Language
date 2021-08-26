/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:23:24 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/23 13:23:31 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_header.h"

static void	philo_eat(t_philo *philo, t_params *params)
{
	long	begin_time;

	sem_wait(params->forks);
	print_message(params, philo->philo_id, "took the left fork");
	sem_wait(params->forks);
	print_message(params, philo->philo_id, "took the right fork");
	sem_wait(params->meal);
	print_message(params, philo->philo_id, "is eating");
	sem_post(params->meal);
	begin_time = get_curr_time();
	while (!params->stop_flag)
	{
		if (get_diff(begin_time, get_curr_time()) >= params->time_to_eat)
			break ;
		usleep(50);
	}
	sem_post(params->forks);
	sem_post(params->forks);
	philo->meal_count++;
	philo->last_meal = get_curr_time();
}

static void	*check_death(void *data)
{
	t_philo		*philo;
	t_params	*params;

	philo = (t_philo *)data;
	params = philo->s_params;
	while (1)
	{
		sem_wait(params->meal);
		if (get_diff(philo->last_meal, get_curr_time()) > params->time_to_die)
		{
			print_message(params, philo->philo_id, "is died");
			params->stop_flag = 1;
			sem_wait(params->console);
			exit(1);
		}
		sem_post(params->meal);
		if (params->meal_count != -1 && philo->meal_count >= params->meal_count)
		{
			params->is_all_ate = 1;
			break ;
		}
		usleep(1000);
	}
	exit(0);
}

static void	philo_sleep(t_philo *philo, t_params *params)
{
	long	begin_time;

	print_message(params, philo->philo_id, "is sleeping");
	begin_time = get_curr_time();
	while (!params->stop_flag)
	{
		if (get_diff(begin_time, get_curr_time()) >= params->time_to_sleep)
			break ;
		usleep(50);
	}
}

static void	start_processes(void *data, t_params *params)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->last_meal = get_curr_time();
	pthread_create(&(philo->thread_id), NULL, check_death, data);
	if (philo->philo_id % 2)
		usleep(15000);
	while (!params->stop_flag && params->is_all_ate != 1)
	{
		philo_eat(philo, params);
		if (philo->meal_count >= params->meal_count && params->meal_count != -1)
			break ;
		print_message(params, philo->philo_id, "is sleeping");
		philo_sleep(philo, params);
		print_message(params, philo->philo_id, "is thinking");
	}
	pthread_join(philo->thread_id, NULL);
	if (params->stop_flag)
		exit(1);
	exit(0);
}

int	start_lifecycle(t_params *params)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = params->philosophers;
	params->begin_time = get_curr_time();
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
