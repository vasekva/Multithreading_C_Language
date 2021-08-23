/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:31:47 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/23 15:31:49 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HEADER_H
# define MAIN_HEADER_H

# include "errors.h"
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_params	t_params;

typedef enum e_status
{
	eating,
	sleeping,
	thinking,
	taking_l_fork,
	taking_r_fork,
	dead
}				t_status;

typedef struct s_philo
{
	int			philo_id;
	int			last_meal;
	int			sleep_start;
	int			meal_count;
	int			right_fork_id;
	int			left_fork_id;
	t_params	*params;
	t_status	status;
}				t_philo;

typedef struct s_params
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	int				stop_flag;
	int				num_of_philo_eaten;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	console;
	t_philo			**philo_data;
	struct timeval	begin_time;
}				t_params;

/// CHECK_FUNCTIONS.C
int		ft_check_params(int argc, char *argv[]);

/**
 * LIFECYCLE_UTILS.C
 */
int		run_lifecycle(t_params *params);
int		get_time(struct timeval start);

/**
 * LIFECYCLE_UTILS_1.C
 */
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *destination, int c, size_t n);

/**
 * LIFECYCLE_UTILS_2.C
 */
char	*ft_itoa(int n);
int		exception(char *str);

/**
 * ACTIONS.C
 */
int		print_message(t_philo *philo);
int		start_meal(t_philo *philo, int process_time);
int		finish_meal(t_philo *philo, int process_time);
void	check_philo(t_philo *philo, int process_time);
#endif
