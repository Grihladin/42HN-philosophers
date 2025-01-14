/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:10:25 by mratke            #+#    #+#             */
/*   Updated: 2025/01/14 20:02:33 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	to_sleep(t_philosopher *philo)
{
	produce_messege(philo->table, philo->id, "is sleeping");
	ft_usleep(philo->table->start, philo->table->time_to_sleep);
}

void	to_think(t_philosopher *philo)
{
	produce_messege(philo->table, philo->id, "is thinking");
}

void	to_eat(t_philosopher *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&philo->table->forks[first_fork]);
	produce_messege(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[second_fork]);
	produce_messege(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->table->death_mutex);
	philo->last_meal_time = get_current_time(philo->table->start);
	pthread_mutex_unlock(&philo->table->death_mutex);
	produce_messege(philo->table, philo->id, "is eating");
	philo->meals_eaten++;
	ft_usleep(philo->table->start, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks[second_fork]);
	pthread_mutex_unlock(&philo->table->forks[first_fork]);
}

void	*start_protocol(void *arg)
{
	t_philosopher	*philo;

	int should_continue ;
	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
	{
		usleep(500);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		should_continue = (!philo->table->someone_died
				&& !philo->table->limit_reached);
		pthread_mutex_unlock(&philo->table->death_mutex);
		if (!should_continue)
			break ;
		to_think(philo);
		to_eat(philo);
		to_sleep(philo);
	}
	return (NULL);
}
