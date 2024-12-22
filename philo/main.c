/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:39:16 by mratke            #+#    #+#             */
/*   Updated: 2024/12/22 01:03:01 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*to_sleep(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	produce_messege(philo->table, philo->id, "is sleeping.");
	return (NULL);
}

void	init_philosophers(t_table *table)
{
	int	i;

	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	table->output = NULL;
	i = 0;
	while (i < table->num_philos)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % table->num_philos;
		table->philosophers[i].table = table;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	start_simulathion(t_table *table)
{
	int			i;
	pthread_t	printing;

	i = 0;
	table->start = malloc(sizeof(t_timeval));
	gettimeofday(table->start, NULL);
	init_philosophers(table);
	while (i < table->num_philos)
	{
		pthread_create(&table->philosophers[i].thread, NULL, to_sleep,
			&table->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
	print_list(table->output);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5)
	{
		printf("INVALID INPUT\n");
		return (1);
	}
	get_input(&table, argv);
	start_simulathion(&table);
}
