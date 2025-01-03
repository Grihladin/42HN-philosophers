/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:57:55 by mratke            #+#    #+#             */
/*   Updated: 2024/12/21 00:43:08 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		result;

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

void	get_input(t_table *input, char **argv)
{
	input->num_philos = atoi(argv[1]);
	input->time_to_die = atoi(argv[2]);
	input->time_to_eat = atoi(argv[3]);
	input->time_to_sleep = atoi(argv[4]);
}

void	print_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		printf("Philo's ID: %i\n", table->philosophers[i].id);
		i++;
	}
}

long	current_time(t_timeval *start)
{
	t_timeval	current;
	long		start_microsec;
	long		current_microsec;

	gettimeofday(&current, NULL);
	start_microsec = (start->tv_sec * 1000000) + start->tv_usec;
	current_microsec = (current.tv_sec * 1000000) + current.tv_usec;
	return (current_microsec - start_microsec);
}
