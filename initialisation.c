/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:56:55 by mratke            #+#    #+#             */
/*   Updated: 2025/01/04 17:33:35 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosophers(t_table *table)
{
	int	i;

	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	table->output = NULL;
	i = 0;
	while (i < table->num_philos)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % table->num_philos;
		table->philosophers[i].table = table;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	get_input(t_table *table, char **argv)
{
	table->num_philos = (int)ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
}
