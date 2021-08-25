# ifndef PHILO_H
# define PHILO_H

# include "errors.h"

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

struct s_philo;

typedef struct s_struct_philo
{  
    int         philo_id;
    int         meal_count;
    int         left_fork_id;
    int         right_fork_id;
    long long   last_meal;
    struct s_philo *t_philo;
    pthread_t    thread_id;  
    
}               struct_philo;

typedef enum 
{
    ARG_NUM = 100,
    ARG_NOT_NUM = 102,
    MUST_EAT = 103,
    PHILO_NUM = 104,
    MUTEX = 105,
    LAUNCH = 106
}           err;

typedef struct  s_philo
{
    int         num_of_philo;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         must_eat;
//    int         error;
    int         died;
    int         is_all_ate;
    long long   begin_time;
    pthread_mutex_t mutex_meal;
    pthread_mutex_t forks[250];
    pthread_mutex_t console;
    struct_philo philosophers[250];

}               t_philo;

void		get_philosophers(t_philo *philo);
int			init_mutex(t_philo *philo);
int			get_arg(t_philo *philo, int ac, char **av);
void		display_out(t_philo *philo, int id, char *str);
long long	time_diff(long long past, long long pres);
long long	timestamp(void);
void		*life(void  *philosopher);

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