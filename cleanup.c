/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:39:43 by mratke            #+#    #+#             */
/*   Updated: 2025/01/07 22:45:46 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_unlock(&table->forks[i]);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	lstclear(&table->output, free);
	free(table->philosophers);
}
