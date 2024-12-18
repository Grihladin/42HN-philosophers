/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:39:16 by mratke            #+#    #+#             */
/*   Updated: 2024/12/18 18:32:38 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	to_sleep(t_philosopher *philo)
{
	printf("%d %ld is sleeping\n", philo->id,
		current_time(&philo->table->start));
}

void	init_philosophers(t_table *table, int n_philos)
{
	int	i;

	table->num_philos = n_philos;
	table->philosophers = malloc(sizeof(t_philosopher) * n_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * n_philos);
	i = 0;
	while (i < n_philos)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % n_philos;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	start_simulathion(t_input_vars input)
{
	t_table	table;

	init_philosophers(&table, input.number_of_philosophers);
	print_philos(&table);
	printf("fine");
	// gettimeofday(&socrat.start, NULL);
	// pthread_create(&socrat.thread, NULL, (void *)to_sleep, &socrat);
	// pthread_join(socrat.thread, NULL);
}

int	main(int argc, char **argv)
{
	t_input_vars	input;

	if (argc != 5)
	{
		printf("INVALID INPUT\n");
		return (1);
	}
	get_input(&input, argv);
	start_simulathion(input);
}
