/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:39:16 by mratke            #+#    #+#             */
/*   Updated: 2024/12/21 21:36:56 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cout(t_messege_list *output)
{
	t_messege_list	*current;
	int				i;

	if (!output || !output->content)
	{
		printf("Debug: Empty list or content\n");
		return ;
	}
	i = 0;
	current = output;
	while (1)
	{
		if (!current || !current->content)
		{
			current = output;
			i = 0;
			continue ;
		}
		if (i == current->content->id)
		{
			printf("%lu %i %s\n", current->content->time_stamp,
				current->content->id, current->content->task);
			i++;
		}
		if (current->next)
			current = current->next;
		else
		{
			current = output;
		}
	}
}

void	produce_messege(t_table *table, int id, char *txt)
{
	t_messege		*new_messege;
	t_messege_list	*new_node;

	new_messege = malloc(sizeof(t_messege));
	new_messege->id = id;
	new_messege->task = txt;
	new_messege->time_stamp = current_time(table->start);
	new_node = lstnew(new_messege);
	if (!new_node)
	{
		free(new_messege->task);
		free(new_messege);
		return ;
	}
	lstadd_back(&table->output, new_node);
}

void	to_sleep(t_philosopher *philo)
{
	produce_messege(philo->table, philo->id, "is sleeping.");
}
void	init_philosophers(t_table *table)
{
	int	i;

	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philos);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	table->output = NULL;
	i = 0;
	while (i < table->num_philos)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].left_fork = i;
		table->philosophers[i].right_fork = (i + 1) % table->num_philos;
		table->philosophers[i].table = table;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	start_simulathion(t_table *table)
{
	int			i;
	pthread_t	printing;

	i = 0;
	table->start = malloc(sizeof(t_timeval));
	gettimeofday(table->start, NULL);
	init_philosophers(table);
	while (i < table->num_philos)
	{
		pthread_create(&table->philosophers[i].thread, NULL, (void *)to_sleep,
			(void *)&table->philosophers[i]);
		i++;
	}
	pthread_create(&printing, NULL, (void *)cout, (void *)table->output);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
	// print_list(table->output);
	pthread_join(printing, NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5)
	{
		printf("INVALID INPUT\n");
		return (1);
	}
	get_input(&table, argv);
	start_simulathion(&table);
}
