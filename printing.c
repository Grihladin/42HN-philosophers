/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:43:18 by mratke            #+#    #+#             */
/*   Updated: 2025/01/03 18:28:05 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	produce_messege(t_table *table, int id, char *txt)
{
	t_messege		*new_messege;
	t_messege_list	*new_node;

	new_messege = malloc(sizeof(t_messege));
	new_messege->id = id;
	new_messege->task = txt;
	new_messege->time_stamp = get_current_time(table->start);
	new_node = lstnew(new_messege);
	if (!new_node)
	{
		free(new_messege->task);
		free(new_messege);
		lstclear(&table->output, free);
		return ;
	}
	lstadd_back(&table->output, new_node);
}

static t_messege_list	*find_next_messege(t_messege_list *current,
		long min_timestamp)
{
	t_messege_list	*earliest;
	long			earliest_timestamp;

	earliest = NULL;
	earliest_timestamp = ULONG_MAX;
	while (current)
	{
		if (current->content && current->content->time_stamp > min_timestamp
			&& current->content->time_stamp < earliest_timestamp)
		{
			earliest_timestamp = current->content->time_stamp;
			earliest = current;
		}
		current = current->next;
	}
	return (earliest);
}

void	*print_messege(void *arg)
{
	t_messege_list	*output;
	t_messege_list	*next_to_print;
	long			min_timestamp;

	min_timestamp = -1;
	output = (t_messege_list *)arg;
	while (1)
	{
		next_to_print = find_next_messege(output, min_timestamp);
		if (next_to_print)
		{
			printf("%lu %s\n", next_to_print->content->time_stamp,
				next_to_print->content->task);
			min_timestamp = next_to_print->content->time_stamp;
		}
	}
}
