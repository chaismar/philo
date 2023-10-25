/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:45:59 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/10 18:37:27 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int			i;
	long int	nbr;
	int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		nbr = nbr * 10 + str[i] - 48;
		i++;
	}
	return (nbr * sign);
}

void	ft_putstr_fd(char *s, int fd)
{
	const size_t	len = ft_strlen(s);

	write(fd, s, len);
}

int	is_num(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_atoi(char *str)
{
	int			i;
	long int	nbr;
	int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
		nbr = (nbr * 10) + (str[i++] - 48);
	if (nbr * sign > 2147483647 || nbr * sign < -2147483648
		|| ft_strlen(str) > 11)
		return (0);
	return (1);
}
