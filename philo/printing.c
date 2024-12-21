/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:43:18 by mratke            #+#    #+#             */
/*   Updated: 2024/12/21 21:43:50 by mratke           ###   ########.fr       */
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

void	cout(t_messege_list *output)
{
	t_messege_list	*current;
	int				i;

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
			current = output;
	}
}
