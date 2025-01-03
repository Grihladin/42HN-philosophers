/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:10:25 by mratke            #+#    #+#             */
/*   Updated: 2025/01/03 20:10:03 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*to_sleep(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	produce_messege(philo->table, philo->id, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	return (NULL);
}

void	*to_think(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	produce_messege(philo->table, philo->id, "is thinking");
	return (NULL);
}

void	*to_eat(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	produce_messege(philo->table, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	produce_messege(philo->table, philo->id, "has taken a fork");
	produce_messege(philo->table, philo->id, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	return (NULL);
}
