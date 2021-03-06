/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 22:30:56 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/27 22:30:58 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	*ft_observer(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	while (1)
	{
		i = 0;
		while (i < philo->num_of_philo)
		{
			if (philo->s_params[i].count_of_meal < philo->meal_count)
				break ;
			i++;
		}
		if (i == philo->num_of_philo)
			break ;
		ft_usleep();
	}
	pthread_mutex_lock(&philo->console);
	pthread_mutex_unlock(&philo->dead_philo);
	return (NULL);
}

void	*ft_death_check(void *data)
{
	t_params	*s_params;
	char		*tmp;

	s_params = (t_params *)data;
	while (1)
	{
		pthread_mutex_lock(&s_params->is_dead);
		if (get_curr_time() > s_params->time_to_death)
		{
			pthread_mutex_lock(&s_params->philo->console);
			tmp = ft_itoa(get_curr_time() - s_params->philo->begin_time);
			write(1, tmp, ft_strlen(tmp));
			free(tmp);
			write(1, " #", 2);
			tmp = ft_itoa(s_params->philo_id);
			write(1, tmp, ft_strlen(tmp));
			free(tmp);
			write(1, " died\n", 6);
			pthread_mutex_unlock(&s_params->is_dead);
			pthread_mutex_unlock(&s_params->philo->dead_philo);
			return (NULL);
		}
		ft_usleep();
	}
}

static void	put_str(t_params *s_params, char *str)
{
	char	*tmp;

	pthread_mutex_lock(&s_params->philo->console);
	tmp = ft_itoa(get_curr_time() - s_params->philo->begin_time);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
	write(1, " #", 2);
	tmp = ft_itoa(s_params->philo_id);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	pthread_mutex_unlock(&s_params->philo->console);
}

static void	print_philo_status(void *data)
{
	t_params	*s_params;

	s_params = (t_params *)data;
	pthread_mutex_lock(s_params->left_fork);
	put_str(data, "took the left fork");
	pthread_mutex_lock(s_params->right_fork);
	put_str(data, "took the right fork");
	put_str(data, "is eating");
	usleep(s_params->philo->time_to_eat * 1000);
	pthread_mutex_unlock(s_params->right_fork);
	pthread_mutex_unlock(s_params->left_fork);
	s_params->time_to_death = get_curr_time() + s_params->philo->time_to_die;
	s_params->count_of_meal++;
	put_str(data, "is sleeping");
	usleep(s_params->philo->time_to_sleep * 1000);
	put_str(data, "is thinking");
}

void	*cycle_checks_start(void *data)
{
	pthread_t	thread;
	t_params	*s_params;

	s_params = (t_params *)data;
	if (s_params->is_e_philo)
	{
		ft_usleep();
		s_params->is_e_philo = 0;
	}
	s_params->time_last_meal = get_curr_time();
	s_params->time_to_death
		= s_params->time_last_meal + s_params->philo->time_to_die;
	if (pthread_create(&thread, NULL, &ft_death_check, s_params) != 0)
		return ((void *)1);
	pthread_detach(thread);
	while (s_params->count_of_meal != s_params->philo->meal_count)
		print_philo_status(s_params);
	ft_usleep();
	pthread_mutex_lock(&s_params->philo->console);
	pthread_mutex_unlock(&s_params->philo->dead_philo);
	return (NULL);
}
