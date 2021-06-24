#ifndef MAIN_HEADER_H
# define MAIN_HEADER_H

# include "errors.h"
# include "libft.h"

# include <stdio.h>
# include <unistd.h>

int	ft_check_params(int argc, char *argv[]);
int	exception(char *str);

typedef struct s_philo
{
	int philo_number;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_count;
	int	eating;
	int	thinking;
	int	sleeping;
}				t_philo;

#endif
