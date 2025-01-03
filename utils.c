/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:57:55 by mratke            #+#    #+#             */
/*   Updated: 2025/01/03 19:22:43 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_atoi(const char *str)
{
	size_t	i;
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	get_input(t_table *table, char **argv)
{
	table->num_philos = (int)ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
}

long	get_current_time(t_timeval *start)
{
	t_timeval	current;
	long		start_millisec;
	long		current_millisec;

	gettimeofday(&current, NULL);
	start_millisec = (start->tv_sec * 1000) + (start->tv_usec / 1000);
	current_millisec = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_millisec - start_millisec);
}
