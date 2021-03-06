/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 22:31:54 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/27 22:31:55 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static void	clear_all(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->dead_philo);
	pthread_mutex_destroy(&philo->dead_philo);
	pthread_mutex_destroy(&philo->console);
	i = -1;
	while (++i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
	}
	pthread_mutex_destroy(&philo->dead_philo);
	free(philo->forks);
	free(philo->s_params);
}

static void	init_mutexes(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num_of_philo)
		pthread_mutex_init(&philo->forks[i], NULL);
	pthread_mutex_init(&philo->console, NULL);
	pthread_mutex_init(&philo->dead_philo, NULL);
	pthread_mutex_lock(&philo->dead_philo);
}

static int	init_all(t_philo *philo, int argc, char **argv)
{
	int	i;

	philo->num_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->meal_count = ft_atoi(argv[5]);
	else
		philo->meal_count = -1;
	i = -1;
	philo->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	philo->s_params = (t_params *)
		malloc(sizeof(t_params) * philo->num_of_philo);
	if (philo->s_params == NULL || philo->forks == NULL)
		return (-1);
	while (++i < philo->num_of_philo)
		pthread_mutex_init(&philo->forks[i], NULL);
	pthread_mutex_init(philo->forks, NULL);
	pthread_mutex_init(&philo->console, NULL);
	init_mutexes(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (ft_check_params(argc, &argv[1]) == -1)
		return (-1);
	if (init_all(&philo, argc, argv) == -1)
		return (-1);
	run_lifecycle(&philo);
	clear_all(&philo);
	return (0);
}
