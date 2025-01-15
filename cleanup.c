/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:39:43 by mratke            #+#    #+#             */
/*   Updated: 2025/01/15 00:51:26 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philosophers[i].meals_mutex);
		i++;
	}
	lstclear(&table->output, free);
	free(table->forks);
	free(table->philosophers);
	free(table->start);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->list_mutex);
	pthread_mutex_destroy(&table->limit_reached_mutex);
}
