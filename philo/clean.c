/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:28:05 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/10 20:32:30 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	destroy_threads(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_join(data->philos[i++].thread, NULL) != 0)
		i++;
	}
	return (0);
}

int	destroy_mutex(t_data *data, int limit)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&(data->release)) != 0)
		ft_putstr_fd(MUTEX_DESTROY_ERR, STDERR_FILENO);
	while (i < limit)
	{
		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
			ft_putstr_fd(MUTEX_DESTROY_ERR, STDERR_FILENO);
		i++;
	}
	if (limit == data->nb_philo)
	{
		if (pthread_mutex_destroy(&(data->printing)) != 0)
			ft_putstr_fd(MUTEX_DESTROY_ERR, STDERR_FILENO);
		if (pthread_mutex_destroy(&(data->health_check)) != 0)
			ft_putstr_fd(MUTEX_DESTROY_ERR, STDERR_FILENO);
	}
	free(data);
	return (0);
}
