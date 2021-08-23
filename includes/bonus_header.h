# ifndef BONUS_HEADER_H
#define BONUS_HEADER_H

#include "errors.h"
#include "libft.h"

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <signal.h>

typedef struct	s_params t_params;

typedef struct      s_philo
{
	int             	philo_id;
	int             	meal_count;
	long long       	last_meal;
	pid_t          		process_id;
	t_params			*t_philo;
	pthread_t			thread_id;

}                   t_philo;

typedef struct      s_params
{
	int             num_of_philo;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             meal_count;
	int             died;
	int             all_ate;
	long long       begin_time;
	t_philo			philosophers[250];
	sem_t           *forks;
	sem_t           *console;
	sem_t           *meal;
}                   t_params;

int					exception(char *str);
int					ft_check_params(int argc, char *argv[]);
void                print_message(t_params *params, int id, char *str);
long long	        get_curr_time(void);
long long           time_diff(long long before, long long now);
int                 start_lifecycle(t_params *params);
void    			close_lifecycle(t_params *params);

#endif
