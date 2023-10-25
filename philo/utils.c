/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:11:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/16 10:28:06 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(unsigned long ms)
{
	unsigned long	time;

	time = get_time();
	while (time_diff(get_time(), time) < ms)
		usleep(100);
}

void	print_state(t_data *data, t_philo *philo, char *state)
{
	int	health;

	pthread_mutex_lock(&(data->printing));
	health = check_health(data);
	if (health == 0 && state[0] != 'd')
	{
		pthread_mutex_unlock(&(data->printing));
		return ;
	}
	printf("%lu %d %s\n", time_diff(get_time(), data->start), philo->id, state);
	pthread_mutex_unlock(&(data->printing));
}

int	get_time(void)
{
	struct timeval	time;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = time.tv_sec;
	u = time.tv_usec;
	return (s * 1000 + u / 1000);
}

unsigned long	time_diff(unsigned long a, unsigned long b)
{
	if (a < b)
		return (0);
	return (a - b);
}
