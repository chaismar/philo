/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:44:38 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/16 10:28:17 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_thread(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&(data->release));
	pthread_mutex_unlock(&(data->release));
	if (philo->id % 2 == 0)
		ft_usleep(data->time_to_eat);
	loop(data, philo);
	return (0);
}

int	init_time_to_think(t_data *data)
{
	int	time_1;
	int	time_2;

	if (data->nb_philo % 2 == 0)
		time_1 = (data->time_to_eat) - (data->time_to_sleep);
	else
		time_1 = (2 * data->time_to_eat) - (data->time_to_sleep);
	if (time_1 < 0)
		time_1 = 0;
	time_2 = data->time_to_eat + data->time_to_sleep;
	if (time_1 <= time_2)
		return (time_1);
	else
		return (time_2);
}

int	init_philosopher(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		if (data->philos[i].id % 2 == 0)
		{
			data->philos[i].right_fork_id = i;
			data->philos[i].left_fork_id = (i + 1) % data->nb_philo;
		}
		else
		{
			data->philos[i].right_fork_id = (i + 1) % data->nb_philo;
			data->philos[i].left_fork_id = i;
		}
		data->philos[i].last_meal = 0;
		data->philos[i].meal_count = 0;
		data->philos[i].hungry = 1;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(data->release), NULL))
		return (ft_putstr_fd(MUTEX_ERR, STDERR_FILENO), 1);
	while (i <= data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
		{
			destroy_mutex(data, i);
			return (ft_putstr_fd(MUTEX_ERR, STDERR_FILENO), 1);
		}
		i++;
	}
	if (pthread_mutex_init(&(data->printing), NULL))
	{
		destroy_mutex(data, i);
		return (ft_putstr_fd(MUTEX_ERR, STDERR_FILENO), 1);
	}
	if (pthread_mutex_init(&(data->health_check), NULL))
	{
		destroy_mutex(data, i);
		return (ft_putstr_fd(MUTEX_ERR, STDERR_FILENO), 1);
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->time_to_think = init_time_to_think(data);
	data->dead_end = 0;
	data->all_ate = 0;
	if (data->nb_philo < 1 || data->nb_philo > 200 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (ft_putstr_fd(ARG_ERR, 2), 1);
	if (argv[5])
	{
		data->tot_meals = ft_atoi(argv[5]);
		if (data->tot_meals <= 0)
			return (ft_putstr_fd(MEAL_ERR, 2), 1);
	}
	else
		data->tot_meals = -1;
	if ((init_mutex(data)) == 1)
		return (1);
	init_philosopher(data);
	return (0);
}
