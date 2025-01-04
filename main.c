/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:39:16 by mratke            #+#    #+#             */
/*   Updated: 2025/01/04 19:28:56 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulathion(t_table *table)
{
	pthread_t	printing;
	int			i;

	i = 0;
	table->start = malloc(sizeof(t_timeval));
	gettimeofday(table->start, NULL);
	init_philosophers(table);
	while (i < table->num_philos)
	{
		pthread_create(&table->philosophers[i].thread, NULL, start_protocol,
			&table->philosophers[i]);
		if (i % 2 == 0)
			usleep(100);
		i++;
	}
	pthread_create(&printing, NULL, print_messege, table->output);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(printing, NULL);
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
