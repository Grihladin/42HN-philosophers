/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:46:47 by mratke            #+#    #+#             */
/*   Updated: 2024/12/17 21:05:31 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librarys/libft/libft.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_input_vars
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}						t_input_vars;

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	pthread_t			id;

}						t_philo;

void					get_input(t_input_vars *input, char **argv);
