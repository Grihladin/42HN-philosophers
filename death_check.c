/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:34:04 by mratke            #+#    #+#             */
/*   Updated: 2025/01/09 01:46:31 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_if_dead(t_table *table, int i)
{
	if ((get_current_time(table->start)
			- table->philosophers[i].last_meal_time) >= table->time_to_die)
	{
		produce_messege(table, table->philosophers[i].id, "died");
		table->someone_died = 1;
		return (1);
	}
	if (table->someone_died == 1 || table->limit_reached == 1)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	return (0);
}

static int	check_if_limit_reached(t_table *table, int i)
{
	static int	philos_reached_limit;

	if (table->philosophers[i].meals_eaten == -1)
	{
		return (0);
	}
	else if (table->meals_limit != -1
		&& table->philosophers[i].meals_eaten == table->meals_limit)
	{
		philos_reached_limit++;
		table->philosophers[i].meals_eaten = -1;
		return (0);
	}
	if (philos_reached_limit == table->num_philos)
	{
		table->limit_reached = 1;
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		pthread_mutex_lock(&table->death_mutex);
		i = 0;
		while (i < table->num_philos)
		{
			if (check_if_limit_reached(table, i) == 1)
				return (pthread_mutex_unlock(&table->death_mutex), NULL);
			if (check_if_dead(table, i) == 1)
				return (pthread_mutex_unlock(&table->death_mutex), NULL);
			i++;
		}
		pthread_mutex_unlock(&table->death_mutex);
		usleep(100);
	}
	return (NULL);
}
