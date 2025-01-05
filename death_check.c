/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:34:04 by mratke            #+#    #+#             */
/*   Updated: 2025/01/05 22:23:37 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*death_monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if ((get_current_time(table->start)
					- table->philosophers[i].last_meal_time) > table->time_to_die)
			{
				produce_messege(table, table->philosophers[i].id, "died");
				table->someone_died = 1;
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
