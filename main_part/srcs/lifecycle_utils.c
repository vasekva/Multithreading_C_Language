/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 22:31:17 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/27 22:31:19 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	ft_usleep(void)
{
	usleep(100);
	usleep(100);
	usleep(100);
	usleep(100);
	usleep(100);
	usleep(100);
	usleep(100);
	usleep(100);
	usleep(100);
	usleep(100);
}

long	get_curr_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	start_threads(t_philo *philo)
{
	int			i;
	pthread_t	thread;

	philo->begin_time = get_curr_time();
	if (philo->meal_count != -1)
	{
		if (pthread_create(&thread, NULL, &ft_observer, philo) != 0)
			return (1);
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		philo->s_params[i].time_to_death = get_curr_time() + philo->time_to_die;
		if (pthread_create(&philo->s_params[i].thread, NULL,
				&cycle_checks_start, (void *)(&philo->s_params[i])) != 0)
			return (-1);
		pthread_detach(philo->s_params[i].thread);
		i++;
	}
	return (0);
}

void	run_lifecycle(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num_of_philo)
	{
		philo->s_params[i].time_last_meal = 0;
		philo->s_params[i].count_of_meal = 0;
		philo->s_params[i].philo_id = i + 1;
		philo->s_params[i].is_e_philo = 0;
		if ((philo->s_params[i].philo_id % 2) == 0)
			philo->s_params[i].is_e_philo = 1;
		philo->s_params[i].left_fork = &philo->forks[i];
		philo->s_params[i].right_fork
			= &philo->forks[(i + 1) % philo->num_of_philo];
		philo->s_params[i].philo = philo;
	}
	start_threads(philo);
}
