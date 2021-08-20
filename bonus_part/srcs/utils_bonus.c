#include "bonus_header.h"

void    display_out(t_params *params, int id, char *str)
{
    sem_wait(params->console);
	if (params->died == 0)
	{
		printf("%lli ", timestamp() - params->start_time);
		printf("#%d ", id + 1);
		printf("%s\n", str);
	}
	sem_post(params->console);
    return ;
}

long long time_diff(long long past, long long pres)
{
    return (pres - past);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}