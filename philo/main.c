/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:27:21 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/16 10:19:55 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->health_check));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(data->health_check));
	print_state(data, philo, EATING);
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&(data->health_check));
	philo->meal_count++;
	pthread_mutex_unlock(&(data->health_check));
}

void	loop(t_data *data, t_philo *philo)
{
	while (1)
	{
		if (check_health(data) == 0)
			break ;
		pthread_mutex_lock(&(data->forks[philo->right_fork_id]));
		print_state(data, philo, FORK);
		if (data->nb_philo == 1)
		{
			pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
			return (ft_usleep(data->time_to_die));
		}
		pthread_mutex_lock(&(data->forks[philo->left_fork_id]));
		print_state(data, philo, FORK);
		eat(data, philo);
		pthread_mutex_unlock(&(data->forks[philo->right_fork_id]));
		pthread_mutex_unlock(&(data->forks[philo->left_fork_id]));
		print_state(data, philo, SLEEPING);
		ft_usleep(data->time_to_sleep);
		print_state(data, philo, THINKING);
		ft_usleep(data->time_to_think);
	}
}

void	loop_thread_principal(t_data *data, int eat, int i)
{
	int	vitals;

	vitals = 0;
	while (1)
	{
		i = 0;
		if (check_health(data) == 0)
			break ;
		while (i < data->nb_philo)
		{
			vitals = check_vitals(data, i);
			if (vitals == 1)
				break ;
			if (vitals == 2)
				eat++;
			if (eat == data->nb_philo)
			{
				pthread_mutex_lock(&(data->health_check));
				data->all_ate = 1;
				pthread_mutex_unlock(&(data->health_check));
			}
			i++;
		}
		usleep(100);
	}
}

int	start_loop(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->release));
	while (i < data->nb_philo)
	{
		if (pthread_create(&(data->philos[i].thread), \
		NULL, init_thread, &(data->philos[i])))
			return (destroy_threads(data, i), \
			ft_putstr_fd(THREAD_ERR, STDERR_FILENO), 1);
		i++;
	}
	data->start = get_time();
	while (i >= 0)
	{
		pthread_mutex_lock(&(data->health_check));
		data->philos[i].last_meal = get_time();
		pthread_mutex_unlock(&(data->health_check));
		i--;
	}
	pthread_mutex_unlock(&(data->release));
	loop_thread_principal(data, 0, 0);
	destroy_threads(data, data->nb_philo);
	destroy_mutex(data, data->nb_philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_args(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), 1);
	if (init_data(data, argv))
		return (free(data), 1);
	if (start_loop(data))
		return (destroy_mutex(data, data->nb_philo), 1);
	else
		return (0);
}
