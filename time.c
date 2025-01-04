/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:25:27 by mratke            #+#    #+#             */
/*   Updated: 2025/01/04 15:27:03 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long time_to_sleep_ms)
{
	if (time_to_sleep_ms <= 0)
	{
		return ;
	}
	while (time_to_sleep_ms > 0)
	{
		usleep(1000);
		time_to_sleep_ms--;
	}
}

long	get_current_time(t_timeval *start)
{
	t_timeval	current;
	long		start_millisec;
	long		current_millisec;

	gettimeofday(&current, NULL);
	start_millisec = (start->tv_sec * 1000) + (start->tv_usec / 1000);
	current_millisec = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_millisec - start_millisec);
}
