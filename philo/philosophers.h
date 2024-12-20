/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:46:47 by mratke            #+#    #+#             */
/*   Updated: 2024/12/21 00:52:17 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct timeval	t_timeval;

typedef struct s_philosopher
{
	int					id;
	int					left_fork;
	int					right_fork;
	pthread_t			thread;
	int					eating;
	int					meals_eaten;
	long				last_meal_time;
	struct s_table		*table;
}						t_philosopher;

typedef struct s_table
{
	t_timeval			*start;
	pthread_mutex_t		*forks;
	t_philosopher		*philosophers;
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}						t_table;

void					get_input(t_table *input, char **argv);
long					current_time(t_timeval *start);
