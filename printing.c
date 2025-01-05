/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:43:18 by mratke            #+#    #+#             */
/*   Updated: 2025/01/05 20:15:26 by mratke           ###   ########.fr       */
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
	new_messege->is_printed = 0;
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

static long	get_earliest_time(t_messege_list *output)
{
	long			min_time;
	t_messege_list	*current;

	min_time = -1;
	current = output;
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
	return (min_time);
}

static t_messege_list	*find_next_messege(t_messege_list *output)
{
	long			min_time;
	t_messege_list	*current;

	current = output;
	min_time = get_earliest_time(current);
	while (current)
	{
		if (current->content->is_printed == 0
			&& current->content->time_stamp == min_time)
		{
			current->content->is_printed = 1;
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

void	*print_messege(void *arg)
{
	t_messege_list	*output;
	t_messege_list	*next_to_print;

	output = (t_messege_list *)arg;
	while (1)
	{
		next_to_print = find_next_messege(output);
		if (next_to_print)
		{
			printf("%lu %i %s\n", next_to_print->content->time_stamp,
				next_to_print->content->id, next_to_print->content->task);
			if (ft_strcmp("died", next_to_print->content->task) == 0)
				break ;
			usleep(1000);
		}
	}
	return (NULL);
}
