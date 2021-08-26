#include "tmp_header.h"

int	init_struct(t_philo *philo, int argc, char **argv)
{
	int i;

	philo->num_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->meal_count = ft_atoi(argv[5]);
	else
		philo->meal_count = -1;
	i = -1;
	philo->forks = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	if (!philo->forks)
		return (-1);
	while (++i < philo->num_of_philo)
		pthread_mutex_init(&philo->forks[i], NULL);
	pthread_mutex_init(philo->forks, NULL);
	pthread_mutex_init(&philo->message, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo 	philo;

	if (ft_check_params(argc, &argv[1]) == -1)
		return (-1);
	if (init_struct(&philo, argc, argv) == -1)
		return (-1);
	philo.s_params = (t_params *)malloc(sizeof(t_params) * philo.num_of_philo);
	if (philo.s_params == NULL || philo.forks == NULL)
		return (-1);
	start_game(&philo);
	pthread_mutex_lock(&philo.dead_philo);
	free_clean(&philo);
	return (0);
}
