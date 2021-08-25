/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberegon <jberegon@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:45:19 by jberegon          #+#    #+#             */
/*   Updated: 2021/08/25 18:45:21 by jberegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_header.h"

static void	print_num_str(int number)
{
	char	*tmp;

	tmp = ft_itoa(number);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
}

void    display_out(t_params *params, int id, char *str)
{
	pthread_mutex_lock(&(params->console));
	if (!params->stop_flag)
	{
		print_num_str((int)(get_curr_time() - params->begin_time));
		write(1, " #", 2);
		print_num_str(id + 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&(params->console));
    return ;
}

long	time_diff(long before, long now)
{
	return (now - before);
}

long	get_curr_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
