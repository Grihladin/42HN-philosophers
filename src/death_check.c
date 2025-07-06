/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:34:04 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 03:54:22 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_if_dead(t_table *table, int i)
{
	long	last_meal;
	long	current_time;

	pthread_mutex_lock(&table->philosophers[i].meals_mutex);
	last_meal = table->philosophers[i].last_meal_time;
	pthread_mutex_unlock(&table->philosophers[i].meals_mutex);
	
	current_time = get_current_time(table->start);
	if (current_time - last_meal > table->time_to_die)
	{
		pthread_mutex_lock(&table->death_mutex);
		if (table->someone_died == 0)
		{
			table->someone_died = 1;
			produce_message(table, table->philosophers[i].id, "died");
		}
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
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
	int		check_delay;

	table = (t_table *)arg;
	if (table->time_to_die < 100)
		check_delay = 100;
	else
		check_delay = table->time_to_die / 10;
	if (check_delay > 1000)
		check_delay = 1000;
	
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
		usleep(check_delay);
	}
	return (NULL);
}
