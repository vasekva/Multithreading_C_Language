#include "main_header.h"

int	ft_check_philo_number(char *argv)
{
	if (ft_strlen(argv) == 1 && (argv[0] <= '1'))
		return (exception(FOUR));
	if (ft_strlen(argv) > 3)
		return (exception(FOUR));
	if (ft_strlen(argv) == 3)
	{
		if (argv[0] > '3')
			return (exception(FOUR));
		if (argv[0] == '2' && (argv[2] != '0' || argv[1] != '0'))
			return (exception(FOUR));
	}
	return (1);
}

int	is_number_positive_array(char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		while (array[i][j])
		{
			if (array[i][j] < 48 || array[i][j] > 57)
				return (exception(THREE));
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	ft_check_params(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc < 5)
		return (exception(ONE));
	if (argc > 6)
		return (exception(TWO));
	if (!is_number_positive_array(&argv[1]))
		return (-1);
	if (!ft_check_philo_number(argv[1]))
		return (-1);
	return (1);
}
