/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:57:55 by mratke            #+#    #+#             */
/*   Updated: 2025/01/05 22:59:42 by mratke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	size_t	i;
	long	sign;
	long	result;

	if (ft_strlen(str) > 7)
		return (-1);
	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_strcmp(const char *lhs, const char *rhs)
{
	size_t	i;

	i = 0;
	while (lhs[i] == rhs[i])
	{
		if (lhs[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return ((unsigned char)lhs[i] - (unsigned char)rhs[i]);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
