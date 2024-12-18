/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:46:47 by mratke            #+#    #+#             */
/*   Updated: 2024/12/18 18:31:32 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librarys/libft/libft.h"
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
	struct s_table		*table;
	int					eating;
	int					meals_eaten;
	long				last_meal_time;
}						t_philosopher;

typedef struct s_table
{
	t_timeval			start;
	int					num_philos;
	pthread_mutex_t		*forks;
	t_philosopher		*philosophers;
}						t_table;

typedef struct s_input_vars
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}						t_input_vars;

void					get_input(t_input_vars *input, char **argv);
long					current_time(t_timeval *start);
void					print_philos(t_table *table);
