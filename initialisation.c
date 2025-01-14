/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:56:55 by mratke            #+#    #+#             */
/*   Updated: 2025/01/14 20:03:46 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosophers(t_table *table)
{
	int	i;

	table->start = malloc(sizeof(t_timeval));
	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	table->output = NULL;
	table->someone_died = 0;
	table->limit_reached = 0;
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->list_mutex, NULL);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		table->philosophers[i].id = i + 1;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % table->num_philos;
		table->philosophers[i].table = table;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].meals_eaten = 0;
		i++;
	}
	gettimeofday(table->start, NULL);
}

int	get_input(t_table *table, char **argv, int argc)
{
	if (argc != 5 && argc != 6)
		return (1);
	table->num_philos = (int)ft_atoi(argv[1]);
	if (table->num_philos > 200 || table->num_philos <= 0)
		return (1);
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die <= 0)
		return (1);
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat <= 0)
		return (1);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep <= 0)
		return (1);
	table->meals_limit = -1;
	if (argc == 6)
	{
		table->meals_limit = (int)ft_atoi(argv[5]);
		if (table->meals_limit <= 0)
			return (1);
	}
	return (0);
}
