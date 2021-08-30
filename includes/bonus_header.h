/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:37:29 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/23 15:37:30 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_HEADER_H
# define BONUS_HEADER_H

# include "errors.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_params	t_params;

typedef struct s_philo
{
	int			philo_id;
	int			meal_count;
	long		last_meal;
	pid_t		process_id;
	t_params	*s_params;
	pthread_t	thread_id;

}	t_philo;

typedef struct s_params
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meal_count;
	int		stop_flag;
	int		is_all_ate;
	long	begin_time;
	t_philo	philosophers[200];
	sem_t	*forks;
	sem_t	*console;
	sem_t	*meal;
}	t_params;

/// CHECK_FUNCTIONS.C
int		ft_check_params(int argc, char *argv[]);

/**
 * ACTIONS.C
 */
int		start_lifecycle(t_params *params);

/**
 * LIFECYCLE_UTILS.C
 */
long	get_curr_time(void);
long	get_diff(long before, long now);
void	print_message(t_params *params, int id, char *str);
void	ft_usleep(void);

/**
 * LIB_FUNCTIONS.C
 */
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *destination, int c, size_t n);

/**
 * ITOA_EXCEPTION.C
 */
char	*ft_itoa(int n);
int		exception(char *str);

#endif
