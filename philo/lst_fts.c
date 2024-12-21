/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:12:06 by mratke            #+#    #+#             */
/*   Updated: 2024/12/21 20:59:29 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lstadd_back(t_messege_list **lst, t_messege_list *new)
{
	t_messege_list	*current;

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

t_messege_list	*lstnew(void *content)
{
	t_messege_list	*new_node;

	new_node = (t_messege_list *)malloc(sizeof(t_messege_list));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->next = NULL;
	new_node->content = content;
	return (new_node);
}

void	lstiter(t_messege_list *lst, void (*f)(void *))
{
	t_messege_list	*current;

	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
	return ;
}

void	lstclear(t_messege_list **lst, void (*del)(void *))
{
	t_messege_list	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	return ;
}

void	print_list(t_messege_list *lst)
{
	t_messege_list	*current;

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
