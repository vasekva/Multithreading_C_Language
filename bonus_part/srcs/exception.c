#include "bonus_header.h"

int	exception(char *str)
{
	int	i;

	i = 0;
	write(1, "Error: ", 7);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (-1);
}
