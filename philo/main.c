/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:39:16 by mratke            #+#    #+#             */
/*   Updated: 2024/12/17 21:11:15 by mratke           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_input_vars	*input;
	pthread_t		philo_id;
	t_timeval		tv;

	if (argc != 5)
	{
		printf("INVALID INPUT\n");
		return (1);
	}
	philo_id = NULL;
	input = malloc(sizeof(t_input_vars));
	get_input(input, argv);
	gettimeofday(&tv, NULL);
	printf("Current time: %ld seconds and %d microseconds\n", tv.tv_sec,
		tv.nsec);
	pthread_create(&philo_id, NULL, (void *)print_input_vars, input);
	pthread_join(philo_id, NULL);
}
