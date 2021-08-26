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
	long		start;
	long		time_to_eat;
	long		time_to_sleep;
	int			meal_count;
	long		time_to_die;
	t_params	*s_params;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	message;
}	t_philo;

typedef struct s_params
{
	int				how_dead;
	int				even;
	int				eaten;
	int				nbr;
	long			last_eat;
	long			time_to_death;
	pthread_t		thread;
	pthread_mutex_t	check;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_philo			*all;
}				t_params;

int	exception(char *str);

int			ft_digits(char *str);
void		start_game(t_philo *philo);
long		get_time(void);
void		message(char *str, t_params *s_params);
void		loop_live(void *tmp);
void		*checkers(void *tmp);
void		free_clean(t_philo *philo);

/// CHECK_FUNCTIONS.C
int		ft_check_params(int argc, char *argv[]);


/**
 * LIFECYCLE_UTILS_1.C
 */
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *destination, int c, size_t n);


#endif
