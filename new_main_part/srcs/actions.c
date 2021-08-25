/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:44:53 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/25 18:44:58 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_header.h"

void    philo_eat(t_philo *philo, t_params *params)
{
	long i;

    pthread_mutex_lock(&(params->forks[philo->left_fork_id]));
    display_out(params, philo->philo_id, "took the left fork");
    pthread_mutex_lock(&(params->forks[philo->right_fork_id]));
    display_out(params, philo->philo_id, "took the right fork");
	pthread_mutex_lock(&(params->mutex_meal));
	display_out(params, philo->philo_id, "is eating");
	philo->last_meal = get_curr_time();
	pthread_mutex_unlock(&(params->mutex_meal));
	i = get_curr_time();
    while (!params->stop_flag)
    {
    	if (time_diff(i, get_curr_time()) >= params->time_to_eat)
            break;
        usleep(50);
    }
	(philo->meal_count)++;
	pthread_mutex_unlock(&(params->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(params->forks[philo->right_fork_id]));
}

void    philo_sleep(t_params *params, t_philo *philo)
{
    long i;

    display_out(params, philo->philo_id, "sleeping");
    i = get_curr_time();
    while (!params->stop_flag)
    {
    	if (time_diff(i, get_curr_time()) >= params->time_to_sleep)
            break;
        usleep(50);
    }
}

void    *life(void  *data)
{
    t_philo    *philo;
    t_params         *params;

    philo = (t_philo  *)data;
    params = philo->s_params;
    if (philo->philo_id % 2)
        usleep(15000);
    while (!params->stop_flag)
    {
    	philo_eat(philo, params);
        if (params->is_all_ate)
            break;
        philo_sleep(params, philo);
//        display_out(new_main_part, phi_str->philo_id, "eating");
    }
    return (NULL);
}
