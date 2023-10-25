/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:12:16 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/16 11:41:51 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_vitals(t_data *data, int i)
{
	pthread_mutex_lock(&(data->health_check));
	if (time_diff(get_time(), data->philos[i].last_meal)
		> (unsigned long)data->time_to_die)
	{
		data->dead_end = 1;
		pthread_mutex_unlock(&(data->health_check));
		print_state(data, &(data->philos[i]), DIED);
		return (1);
	}
	if (data->tot_meals > 0 && data->philos[i].hungry == 1)
	{
		if (data->philos[i].meal_count >= data->tot_meals)
		{
			data->philos[i].hungry = 0;
			pthread_mutex_unlock(&(data->health_check));
			return (2);
		}
	}
	pthread_mutex_unlock(&(data->health_check));
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 4 || argc > 6)
	{
		ft_putstr_fd(ARG_NB_ERR, STDERR_FILENO);
		return (1);
	}
	while (i < argc)
	{
		if (is_num(argv[i]) == 0)
			return (ft_putstr_fd(ARG_ERR, STDERR_FILENO), 1);
		if (check_atoi(argv[i]) == 0)
			return (ft_putstr_fd(ARG_LIMIT_ERR, STDERR_FILENO), 1);
		i++;
	}
	return (0);
}

int	check_health(t_data *data)
{
	int	i;

	pthread_mutex_lock(&(data->health_check));
	if (data->all_ate || data->dead_end)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(&(data->health_check));
	return (i);
}
