/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:34:04 by mratke            #+#    #+#             */
/*   Updated: 2025/01/07 19:26:05 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*death_monitor(void *arg)
{
	t_table	*table;
	int		i;
	int		philos_reached_limit;

	philos_reached_limit = 0;
	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (table->philosophers[i].meals_eaten == -1)
			{
				i++;
				continue ;
			}
			else if (table->meals_limit != -1
				&& table->philosophers[i].meals_eaten == table->meals_limit)
			{
				philos_reached_limit++;
				table->philosophers[i].meals_eaten = -1;
				i++;
			}
			if (philos_reached_limit == table->num_philos)
			{
				table->limit_reached = 1;
				return (NULL);
			}
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
