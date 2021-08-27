#ifndef TMP_HEADER_H
# define TMP_HEADER_H

# include <string.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include "errors.h"

typedef struct s_params t_params;

typedef struct s_philo
{
	int			num_of_philo;
	long		begin_time;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			meal_count;
	t_params	*s_params;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	console;
}	t_philo;

typedef struct s_params
{
	int				how_dead;
	int				even;
	int				eaten;
	int				philo_id;
	long			last_eat;
	long			time_to_death;
	pthread_t		thread;
	pthread_mutex_t	is_dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_philo			*all;
}				t_params;


void		*ft_death_check(void *data);
void	*ft_observer(void *data);
void	*cycle_checks_start(void *data);

void	my_usleep(long time);


/// CHECK_FUNCTIONS.C
int		ft_check_params(int argc, char *argv[]);

/**
 * LIFECYCLE_UTILS.C
 */
void		run_lifecycle(t_philo *philo);
long		get_curr_time(void);

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
