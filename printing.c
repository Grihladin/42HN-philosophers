/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:43:18 by mratke            #+#    #+#             */
/*   Updated: 2025/07/06 03:54:22 by mratke           ###   ########.fr       */
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
	pthread_mutex_lock(&table->list_mutex);
	new_message->time_stamp = get_current_time(table->start);
	lstadd_back(&table->output, new_node);
	pthread_mutex_unlock(&table->list_mutex);
}

static t_message_list	*find_next_message(t_table *table)
{
	t_message_list	*current;
	t_message_list	*result;
	long			min_time;

	result = NULL;
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
				result = current;
			}
		}
		current = current->next;
	}
	if (result)
		result->content->is_printed = 1;
	pthread_mutex_unlock(&table->list_mutex);
	return (result);
}

int	print_message(t_table *table)
{
	t_message_list	*next_to_print;
	int				limit_reached;
	int				no_message_count;

	limit_reached = 0;
	no_message_count = 0;
	while (1)
	{
		pthread_mutex_lock(&table->death_mutex);
		limit_reached = table->limit_reached;
		pthread_mutex_unlock(&table->death_mutex);
		if (limit_reached == 1)
			break ;
		next_to_print = find_next_message(table);
		if (next_to_print)
		{
			printf("%lu %i %s\n", next_to_print->content->time_stamp,
				next_to_print->content->id, next_to_print->content->task);
			if (ft_strcmp("died", next_to_print->content->task) == 0)
				break ;
			no_message_count = 0;
		}
		else
		{
			no_message_count++;
			if (no_message_count > 5)
				usleep(PRINT_DELAY * 2);
			else
				usleep(PRINT_DELAY);
		}
	}
	return (1);
}
