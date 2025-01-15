/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:46:47 by mratke            #+#    #+#             */
/*   Updated: 2025/01/15 01:44:19 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

// microseconds
#define PRINT_DELAY 10000
#define MONITOR_DELAY 2500
#define DEFAULT_DELAY 1000
#define PRECISE_TIME_CALC_DELAY 50

typedef struct timeval		t_timeval;

typedef struct s_messege
{
	int						id;
	char					*task;
	long					time_stamp;
	int						is_printed;
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
	pthread_mutex_t			meals_mutex;
	int						eating;
	int						meals_eaten;
	long					last_meal_time;
	struct s_table			*table;
}							t_philosopher;

typedef struct s_table
{
	pthread_mutex_t			death_mutex;
	pthread_mutex_t			list_mutex;
	int						someone_died;
	int						limit_reached;
	t_messege_list			*output;
	t_timeval				*start;
	pthread_mutex_t			*forks;
	t_philosopher			*philosophers;
	int						num_philos;
	int						meals_limit;
	int						philos_reached_limit;
	pthread_mutex_t			limit_reached_mutex;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
}							t_table;

// init

int							get_input(t_table *input, char **argv, int arc);
void						init_philosophers(t_table *table);

// lst

void						lstadd_back(t_messege_list **lst,
								t_messege_list *new);
t_messege_list				*lstnew(void *content);
void						lstiter(t_messege_list *lst, void (*f)(void *));
void						lstclear(t_messege_list **lst, void (*del)(void *));
void						print_list(t_messege_list *lst);

// time

long						get_current_time(t_timeval *start);
void						ft_usleep(t_timeval *start, long time_to_sleep_ms);

// protocol

void						to_sleep(t_philosopher *philo);
void						to_think(t_philosopher *philo);
void						to_eat(t_philosopher *philo);
void						*start_protocol(void *arg);

// death monitor

void						*death_monitor(void *arg);

// printing staff

void						*print_messege(void *arg);
void						produce_messege(t_table *table, int id, char *txt);

// utils

long						ft_atoi(const char *str);
int							ft_strcmp(const char *lhs, const char *rhs);
int							ft_strlen(const char *str);
void						clean_all(t_table *table);
