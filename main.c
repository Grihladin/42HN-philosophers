/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:39:16 by mratke            #+#    #+#             */
/*   Updated: 2025/01/14 20:03:27 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulathion(t_table *table)
{
	pthread_t	check_death;
	int			i;
	pthread_t	printing;

	i = 0;
	init_philosophers(table);
	while (i < table->num_philos)
	{
		pthread_create(&table->philosophers[i].thread, NULL, start_protocol,
			&table->philosophers[i]);
		if (i % 2 == 0)
			usleep(100);
		i++;
	}
	pthread_create(&printing, NULL, print_messege, table);
	pthread_create(&check_death, NULL, death_monitor, table);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(printing, NULL);
	pthread_join(check_death, NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (get_input(&table, argv, argc) == 1)
	{
		printf("Invalid args\n");
		return (1);
	}
	start_simulathion(&table);
	clean_all(&table);
}
