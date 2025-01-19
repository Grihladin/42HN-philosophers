/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:43:18 by mratke            #+#    #+#             */
/*   Updated: 2025/01/19 18:09:59 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	produce_message(t_table *table, int id, char *txt)
{
	t_message		*new_message;
	t_message_list	*new_node;

	new_message = malloc(sizeof(t_message));
	new_message->id = id;
	new_message->task = txt;
	pthread_mutex_lock(&table->list_mutex);
	new_message->time_stamp = get_current_time(table->start);
	new_message->is_printed = 0;
	new_node = lstnew(new_message);
	if (!new_node)
	{
		free(new_message->task);
		free(new_message);
		lstclear(&table->output, free);
		pthread_mutex_unlock(&table->list_mutex);
		return ;
	}
	lstadd_back(&table->output, new_node);
	pthread_mutex_unlock(&table->list_mutex);
}

static long	get_earliest_time(t_table *table)
{
	long			min_time;
	t_message_list	*current;

	min_time = -1;
	pthread_mutex_lock(&table->list_mutex);
	current = table->output;
	while (current)
	{
		if (current->content->is_printed == 0)
		{
			if (min_time == -1 || current->content->time_stamp < min_time)
			{
				min_time = current->content->time_stamp;
			}
		}
		current = current->next;
	}
	pthread_mutex_unlock(&table->list_mutex);
	return (min_time);
}

static t_message_list	*find_next_message(t_table *table)
{
	long			min_time;
	t_message_list	*current;

	min_time = get_earliest_time(table);
	pthread_mutex_lock(&table->list_mutex);
	current = table->output;
	while (current)
	{
		if (current->content->is_printed == 0
			&& current->content->time_stamp == min_time)
		{
			current->content->is_printed = 1;
			pthread_mutex_unlock(&table->list_mutex);
			return (current);
		}
		current = current->next;
	}
	pthread_mutex_unlock(&table->list_mutex);
	return (NULL);
}

void	*print_message(void *arg)
{
	t_table			*table;
	t_message_list	*next_to_print;

	table = (t_table *)arg;
	while (1)
	{
		next_to_print = find_next_message(table);
		if (next_to_print)
		{
			printf("%lu %i %s\n", next_to_print->content->time_stamp,
				next_to_print->content->id, next_to_print->content->task);
			pthread_mutex_lock(&table->death_mutex);
			if (ft_strcmp("died", next_to_print->content->task) == 0
				|| table->limit_reached == 1)
			{
				pthread_mutex_unlock(&table->death_mutex);
				break ;
			}
			pthread_mutex_unlock(&table->death_mutex);
			usleep(PRINT_DELAY);
		}
	}
	return (NULL);
}
