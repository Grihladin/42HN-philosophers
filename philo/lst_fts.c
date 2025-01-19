/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:12:06 by mratke            #+#    #+#             */
/*   Updated: 2025/01/19 18:11:41 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lstadd_back(t_message_list **lst, t_message_list *new)
{
	t_message_list	*current;

	if (new == NULL)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	return ;
}

t_message_list	*lstnew(void *content)
{
	t_message_list	*new_node;

	new_node = (t_message_list *)malloc(sizeof(t_message_list));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	new_node->content = content;
	return (new_node);
}

void	lstiter(t_message_list *lst, void (*f)(void *))
{
	t_message_list	*current;

	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
	return ;
}

void	lstclear(t_message_list **lst, void (*del)(void *))
{
	t_message_list	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return ;
}

void	print_list(t_message_list *lst)
{
	t_message_list	*current;

	if (!lst)
	{
		printf("List is empty\n");
		return ;
	}
	current = lst;
	while (current)
	{
		if (current->content)
			printf("%lu %d %s\n", current->content->time_stamp,
				current->content->id, current->content->task);
		current = current->next;
	}
}
