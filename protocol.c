/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:10:25 by mratke            #+#    #+#             */
/*   Updated: 2025/01/19 18:31:40 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	to_sleep(t_philosopher *philo)
{
	produce_message(philo->table, philo->id, "is sleeping");
	ft_usleep(philo->table->start, philo->table->time_to_sleep);
}

void	to_think(t_philosopher *philo)
{
	produce_message(philo->table, philo->id, "is thinking");
}

static void	control_forks(t_philosopher *philo, int *first_fork,
		int *second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	else
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
}

void	to_eat(t_philosopher *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = 0;
	second_fork = 0;
	control_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->table->forks[first_fork]);
	produce_message(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[second_fork]);
	produce_message(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal_time = get_current_time(philo->table->start);
	pthread_mutex_unlock(&philo->table->death_mutex);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
	produce_message(philo->table, philo->id, "is eating");
	ft_usleep(philo->table->start, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks[second_fork]);
	pthread_mutex_unlock(&philo->table->forks[first_fork]);
}

void	*start_protocol(void *arg)
{
	t_philosopher	*philo;

	int should_continue ;
	should_continue = 1;
	philo = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		if (philo->table->someone_died == 1 || philo->table->limit_reached == 1)
			should_continue = 0;
		pthread_mutex_unlock(&philo->table->death_mutex);
		if (should_continue == 0)
			break ;
		to_think(philo);
		to_eat(philo);
		to_sleep(philo);
	}
	return (NULL);
}
