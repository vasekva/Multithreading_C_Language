/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 13:23:36 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/23 13:23:38 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_header.h"

static int	check_philo_number(char *philo_number)
{
	if (ft_strlen(philo_number) == 1 && (philo_number[0] <= '0'))
		return (exception(FOUR));
	if (ft_strlen(philo_number) > 3)
		return (exception(FOUR));
	if (ft_strlen(philo_number) == 3)
	{
		if (philo_number[0] > '3')
			return (exception(FOUR));
		if (philo_number[0] == '2'
			&& (philo_number[2] != '0' || philo_number[1] != '0'))
			return (exception(FOUR));
	}
	return (1);
}

static int	is_number_positive_array(char *argv[])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '0')
			return (exception(THREE));
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (exception(THREE));
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static int	ft_check_all_timings(char *argv[])
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;

	time_to_die = ft_atoi(argv[1]);
	time_to_eat = ft_atoi(argv[2]);
	time_to_sleep = ft_atoi(argv[3]);
	if (time_to_die < 60 || time_to_eat < 60 || time_to_sleep < 60)
		return (-1);
	return (0);
}

int	ft_check_params(int argc, char *argv[])
{
	if (argc < 5)
		return (exception(ONE));
	if (argc > 6)
		return (exception(TWO));
	if (ft_check_all_timings(argv) == -1)
		return (exception(FIVE));
	if (is_number_positive_array(argv) == -1)
		return (-1);
	if (check_philo_number(argv[0]) == -1)
		return (-1);
	return (1);
}
