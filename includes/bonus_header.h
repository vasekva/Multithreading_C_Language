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

struct              s_params;

typedef struct      s_philo
{
	int             philo_id;
	long long       last_meal;
	pid_t           pid_id;
	int             meal_count;
	//    int             left_fork;
	//    int             right_fork;
	struct s_params  *t_philo;
	pthread_t      thread_id;

}                   t_philo;

typedef struct      s_params
{
	int             error;
	int             n_philo;
	int             time_die;
	int             time_eat;
	int             time_sleep;
	int             must_eat;
	int             died;
	int             all_ate;
	long long       start_time;
	t_philo			philosophers[250];
	sem_t           *forks;
	sem_t           *console;
	sem_t           *check_meal;

}                   t_params;

typedef enum
{
	ARG_NUM =       100,
	ARG_NOT_NUM =   102,
	MUST_EAT =      103,
	PHILO_NUM =     104,
	MUTEX =         105,
	LAUNCH =        106,
	INIT =          107
}                   err;

int	exception(char *str);
int					ft_check_params(int argc, char *argv[]);
int			        ft_atoi(const char *str);
void                display_out(t_params *params, int id, char *str);
long long	        timestamp(void);
void                ft_error(t_params *params);
long long	        timestamp(void);
long long           time_diff(long long past, long long pres);
int                 get_arg(t_params *params, int ac, char **av);
int                 launch_program(t_params *params);

#endif
