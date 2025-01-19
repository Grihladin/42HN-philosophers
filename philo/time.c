/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:25:27 by mratke            #+#    #+#             */
/*   Updated: 2025/01/15 00:24:18 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(t_timeval *start, long time_to_sleep_ms)
{
	long	start_orig;

	if (time_to_sleep_ms <= 0)
	{
		return ;
	}
	start_orig = get_current_time(start);
	while ((get_current_time(start) - start_orig) < time_to_sleep_ms)
		usleep(PRECISE_TIME_CALC_DELAY);
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
