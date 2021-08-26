# ifndef PHILO_H
# define PHILO_H

# include "errors.h"

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_params t_params;

typedef struct s_philo
{  
    int         philo_id;
    int         meal_count;
    int         left_fork_id;
    int         right_fork_id;
    long 		  last_meal;
    t_params	*s_params;
    pthread_t    thread_id;  
    
}               t_philo;

typedef struct  s_params
{
    int         num_of_philo;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         must_eat;
    int         stop_flag;
    int         is_all_ate;
    int			num_of_philo_eaten;
    long  		begin_time;
    pthread_mutex_t mutex_meal;
    pthread_mutex_t forks[250];
    pthread_mutex_t console;
    t_philo philosophers[250];

}               t_params;

void	print_num_str(int number);

int	init_all(t_params *params, int argc, char *argv[]);

void    	print_message(t_params *params, int id, char *str);
long		get_diff(long before, long now);
long		get_curr_time(void);
void		*start_lifecycle(void  *data);

/// CHECK_FUNCTIONS.C
int		ft_check_params(int argc, char *argv[]);


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

# endif