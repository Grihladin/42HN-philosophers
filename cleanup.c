/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:39:43 by mratke            #+#    #+#             */
/*   Updated: 2025/01/10 21:19:35 by mratke           ###   ########.fr       */
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
		i++;
	}
	lstclear(&table->output, free);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->list_mutex);
	free(table->philosophers);
	free(table->forks);
	free(table->start);
}
