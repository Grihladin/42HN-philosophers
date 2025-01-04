/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:10:25 by mratke            #+#    #+#             */
/*   Updated: 2025/01/04 18:12:54 by mratke           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	produce_messege(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	produce_messege(philo->table, philo->id, "has taken a fork");
	produce_messege(philo->table, philo->id, "is eating");
	ft_usleep(philo->table->start, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

void	*start_protocol(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		to_eat(philo);
		to_sleep(philo);
		to_think(philo);
	}
	return (NULL);
}
