/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:34:04 by mratke            #+#    #+#             */
/*   Updated: 2025/01/20 00:37:03 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_if_dead(t_table *table, int i)
{
	long	last_meal;
	long	current_time;

	pthread_mutex_lock(&table->death_mutex);
	pthread_mutex_lock(&table->philosophers[i].meals_mutex);
	last_meal = table->philosophers[i].last_meal_time;
	current_time = get_current_time(table->start);
	pthread_mutex_unlock(&table->philosophers[i].meals_mutex);
	if (current_time - last_meal > table->time_to_die)
	{
		table->someone_died = 1;
		produce_message(table, table->philosophers[i].id, "died");
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->death_mutex);
	return (0);
}

static void	unlock_limit_checker_mutexes(t_table *table, int i)
{
	pthread_mutex_unlock(&table->philosophers[i].meals_mutex);
	pthread_mutex_unlock(&table->limit_reached_mutex);
}

static void	lock_limit_checker_mutexes(t_table *table, int i)
{
	pthread_mutex_lock(&table->limit_reached_mutex);
	pthread_mutex_lock(&table->philosophers[i].meals_mutex);
}

static int	check_if_limit_reached(t_table *table, int i)
{
	lock_limit_checker_mutexes(table, i);
	if (table->philosophers[i].meals_eaten == -1)
	{
		unlock_limit_checker_mutexes(table, i);
		return (0);
	}
	if (table->meals_limit != -1)
	{
		if (table->philosophers[i].meals_eaten > table->meals_limit)
		{
			if (table->philosophers[i].meals_eaten != -1)
			{
				table->philos_reached_limit++;
				table->philosophers[i].meals_eaten = -1;
			}
			if (table->philos_reached_limit >= table->num_philos)
			{
				table->limit_reached = 1;
				unlock_limit_checker_mutexes(table, i);
				return (1);
			}
		}
	}
	unlock_limit_checker_mutexes(table, i);
	return (0);
}

void	*death_monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (check_if_limit_reached(table, i) == 1 || check_if_dead(table,
					i) == 1)
			{
				return (NULL);
			}
			i++;
		}
		usleep(MONITOR_DELAY);
	}
	return (NULL);
}
