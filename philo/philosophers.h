/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:46:47 by mratke            #+#    #+#             */
/*   Updated: 2024/12/21 20:59:37 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct timeval		t_timeval;

typedef struct s_messege
{
	int						id;
	char					*task;
	long					time_stamp;
}							t_messege;

typedef struct s_messege_list
{
	t_messege				*content;
	struct s_messege_list	*next;
}							t_messege_list;

typedef struct s_philosopher
{
	int						id;
	int						left_fork;
	int						right_fork;
	pthread_t				thread;
	int						eating;
	int						meals_eaten;
	long					last_meal_time;
	struct s_table			*table;
}							t_philosopher;

typedef struct s_table
{
	t_messege_list			*output;
	t_timeval				*start;
	pthread_mutex_t			*forks;
	t_philosopher			*philosophers;
	int						num_philos;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
}							t_table;

void						get_input(t_table *input, char **argv);
long						current_time(t_timeval *start);

// lst

void						lstadd_back(t_messege_list **lst,
								t_messege_list *new);
t_messege_list				*lstnew(void *content);
void						lstiter(t_messege_list *lst, void (*f)(void *));
void						lstclear(t_messege_list **lst, void (*del)(void *));
void						print_list(t_messege_list *lst);
