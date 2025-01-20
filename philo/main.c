/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:39:16 by mratke            #+#    #+#             */
/*   Updated: 2025/01/20 22:47:35 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulathion(t_table *table)
{
	pthread_t	check_death;
	int			i;

	i = 0;
	init_philosophers(table);
	pthread_create(&check_death, NULL, death_monitor, table);
	while (i < table->num_philos)
	{
		pthread_create(&table->philosophers[i].thread, NULL, start_protocol,
			&table->philosophers[i]);
		if (i % 2 == 0)
			usleep(100);
		i++;
	}
	print_message(table);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
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
