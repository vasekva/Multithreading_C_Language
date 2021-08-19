#include "bonus_header.h"

void    check_if_nb(t_params *params, char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] >= '0' && av[i][j] <= '9')
                j++;
            else
            {
                params->error = ARG_NOT_NUM;
                break;
            }
        }
        i++; 
    }
}

void    init_arg(t_params *params, char **av)
{
    params->n_philo = ft_atoi(av[1]);
    if (params->n_philo > 250 || params->n_philo < 1)
        params->error = PHILO_NUM;
    params->time_die = ft_atoi(av[2]);
    params->time_eat = ft_atoi(av[3]);
    params->time_sleep = ft_atoi(av[4]);
    if (av[5])
    {
        params->must_eat = ft_atoi(av[5]);
        if (params->must_eat <= 0)
            params->error = MUST_EAT;
    }
    else
        params->must_eat = -1;
    params->died = 0;
    params->all_ate = 0;
}


int     get_arg(t_params *params, int ac, char **av)
{
	params->error = 0;
    if (ac != 5 && ac != 6)
    	params->error = ARG_NUM;
    check_if_nb(params, av);
    if (params->error != 0)
        return (1);
    else
    	init_arg(params, av);
    return (0);
}