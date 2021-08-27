/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 22:59:08 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/27 22:59:09 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HEADER_H
# define MAIN_HEADER_H

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include "errors.h"

typedef struct s_params	t_params;

typedef struct s_philo
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	long			begin_time;
	t_params		*s_params;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	console;
}				t_philo;

typedef struct s_params
{
	int				is_e_philo;
	int				count_of_meal;
	int				philo_id;
	long			time_last_meal;
	long			time_to_death;
	pthread_t		thread;
	pthread_mutex_t	is_dead;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo			*philo;
}				t_params;

/// CHECK_FUNCTIONS.C
int		ft_check_params(int argc, char *argv[]);

/**
 * CYCLE_FUNCTIONS.C
 */
void	*ft_death_check(void *data);
void	*ft_observer(void *data);
void	*cycle_checks_start(void *data);

/**
 * LIFECYCLE_UTILS.C
 */
void	run_lifecycle(t_philo *philo);
long	get_curr_time(void);
void	my_usleep(long time);

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

#endif
