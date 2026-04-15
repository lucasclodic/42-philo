/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:42:18 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/02 15:55:20 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/philo.h"

int	is_valid_number(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long int	output;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	output = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		output = output * 10 + str[i] - '0';
		if (output > 2147483647)
			return (-1);
		i++;
	}
	return (output);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000000 + tv.tv_usec);
}
