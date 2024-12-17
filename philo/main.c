/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:39:16 by mratke            #+#    #+#             */
/*   Updated: 2024/12/17 22:28:58 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_input_vars(t_input_vars *input)
{
	printf("var1: %d\n", input->number_of_philosophers);
	printf("var2: %d\n", input->time_to_die);
	printf("var3: %d\n", input->time_to_eat);
	printf("var4: %d\n", input->time_to_sleep);
}

long	time_spended(t_timeval *start)
{
	t_timeval	current;
	long		start_microsec;
	long		current_microsec;

	gettimeofday(&current, NULL);
	start_microsec = (start->tv_sec * 1000000) + start->tv_usec;
	current_microsec = (current.tv_sec * 1000000) + current.tv_usec;
	return (current_microsec - start_microsec);
}

int	main(int argc, char **argv)
{
	t_input_vars	*input;
	pthread_t		philo_id;
	t_timeval		start;

	if (argc != 5)
	{
		printf("INVALID INPUT\n");
		return (1);
	}
	philo_id = NULL;
	input = malloc(sizeof(t_input_vars));
	get_input(input, argv);
	gettimeofday(&start, NULL);
	pthread_create(&philo_id, NULL, (void *)print_input_vars, input);
	pthread_join(philo_id, NULL);
	printf("Elapsed time: %ld microseconds\n", time_spended(&start));
}
