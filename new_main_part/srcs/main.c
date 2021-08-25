/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:45:40 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/25 18:45:41 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_header.h"

void    check_if_death(t_params *params, t_philo *philo)
{
    int i;

    while (!(params->is_all_ate))
    {
        i = -1;
        while (++i < params->num_of_philo && !params->stop_flag)
		{
			pthread_mutex_lock(&(params->mutex_meal));
			if (time_diff(philo[i].last_meal, get_curr_time()) > params->time_to_die)
			{
				display_out(params, i, "died");
				params->stop_flag = 1;
			}
			pthread_mutex_unlock(&(params->mutex_meal));
			usleep(100);
		}
        if (params->stop_flag)
			break ;
		i = 0;
		while (params->must_eat != -1 && i < params->num_of_philo && philo[i].meal_count >= params->must_eat)
			i++;
		if (i == params->num_of_philo)
			params->is_all_ate = 1;
    }
}

void    join_destroy(t_params *params, t_philo *philo)
{
    int i;

	i = -1;
	while (++i < params->num_of_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < params->num_of_philo)
		pthread_mutex_destroy(&(params->forks[i]));
	pthread_mutex_destroy(&(params->console));
}

int     start_lifecycle(t_params *params)
{
    int     i;
    t_philo *philo;

    i = 0;
    philo = params->philosophers;
    params->begin_time = get_curr_time();
    while (i < params->num_of_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, life, &(philo[i])))
        {
			return (1);
        }
		philo[i].last_meal = get_curr_time();
		i++;
	}
    check_if_death(params, params->philosophers);
    join_destroy(params, philo);
    return (0);
}

int ft_alone(t_params *params)
{
	if (params->num_of_philo == 1)
    {
		printf("0 1 took the right fork\n");
        usleep(params->time_to_die * 1000);
        printf("%d 1 is dead\n", params->time_to_die);
        return (1);
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
		params->must_eat = ft_atoi(argv[5]);
	else
		params->must_eat = -1;
	params->stop_flag = 0;
	params->is_all_ate = 0;
	return (0);
}

int    init_mutex(t_params *params)
{
	int i;

	i = params->num_of_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(params->forks[i]), NULL))
			return (-1);
	}
	if (pthread_mutex_init(&(params->console), NULL))
		return (-1);
	if (pthread_mutex_init(&(params->mutex_meal), NULL))
		return (-1);
	return (0);
}

void    get_philosophers(t_params *params)
{
	int i;

	i = params->num_of_philo;
	while (--i >= 0)
	{
		params->philosophers[i].philo_id = i;
		params->philosophers[i].meal_count = 0;
		params->philosophers[i].left_fork_id = i;
		params->philosophers[i].right_fork_id = (i + 1) % params->num_of_philo;
		params->philosophers[i].last_meal = 0;
		params->philosophers[i].s_params = params;
	}
}

int main(int argc, char *argv[])
{
    t_params params;

    if (ft_check_params(argc, &argv[1]) == -1)
    	return (-1);
    init_struct(&params, argc, argv);
	if (init_mutex(&params) == -1)
    {
		exception(SIX);
        return (1);
    }
	if (ft_alone(&params))
        return (1);
	get_philosophers(&params);
	if (start_lifecycle(&params))
    {
		exception(SEVEN);
        return (1);
    }
    return (0);
}
