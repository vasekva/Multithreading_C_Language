#include "main_header.h"

int	start_processes(t_philo *philo)
{
	printf("%d\n %d\n %d\n %d\n %d\n %d\n %d\n %d\n",
			philo->philo_number, philo->time_to_die, philo->time_to_eat,
			philo->time_to_sleep, philo->eating, philo->thinking, philo->sleeping,
			philo->eat_count);
	return (0);
}

void	init_struct(t_philo *philo, int argc, char **argv)
{
	philo->philo_number = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->eating = 0;
	philo->thinking = 0;
	philo->sleeping = 0;
	if (argc == 5)
		philo->eat_count = 0;
	else
		philo->eat_count = ft_atoi(argv[5]);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if (!ft_check_params(argc, argv))
		return (-1);
	init_struct(&philo, argc, argv);

	start_processes(&philo);
	return (0);
}
