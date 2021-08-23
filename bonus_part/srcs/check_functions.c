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

static int	check_eat_and_sleep_times(char *str)
{
	if (ft_strlen(str) <= 2)
	{
		if (ft_strlen(str) <= 1)
			return (exception(FIVE));
		if (ft_strlen(str) == 2 && str[0] < '6')
			return (exception(FIVE));
	}
	return (0);
}

int	ft_check_params(int argc, char *argv[])
{
	if (argc < 5)
		return (exception(ONE));
	if (argc > 6)
		return (exception(TWO));
	if (is_number_positive_array(argv) == -1)
		return (-1);
	if (check_philo_number(argv[0]) == -1)
		return (-1);
	if (check_eat_and_sleep_times(argv[2]) == -1
		|| check_eat_and_sleep_times(argv[3]) == -1)
		return (-1);
	return (1);
}
