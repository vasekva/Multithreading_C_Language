#include "bonus_header.h"

void    print_message(t_params *params, int id, char *str)
{

    sem_wait(params->console);
	if (params->died == 0)
	{
		printf("%lli ", get_curr_time() - params->begin_time);
		printf("#%d ", id + 1);
		printf("%s\n", str);
	}
	sem_post(params->console);
    return ;
}

long long time_diff(long long before, long long now)
{
	return (now - before);
}

long long	get_curr_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}