/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:42:18 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/philo.h"

static int	check_death(t_table *table, int i, long long now)
{
	set_stop(table, 1);
	pthread_mutex_lock(&table->print_mutex);
	printf("%lld %d died\n", (now - table->start_time) / 1000,
		table->philos[i].id);
	pthread_mutex_unlock(&table->print_mutex);
	return (1);
}

static int	get_meal_data(t_table *table, int *meals, int i)
{
	long long	last_meal;
	long long	now;

	pthread_mutex_lock(&table->philos[i].meal_mutex);
	last_meal = table->philos[i].last_meal;
	*meals = table->philos[i].meals_eaten;
	now = get_time_in_ms();
	pthread_mutex_unlock(&table->philos[i].meal_mutex);
	if (now - last_meal >= (long long)table->time_to_die * 1000)
		return (check_death(table, i, now));
	return (0);
}

int	monitor_simulation(t_table *table)
{
	int	i;
	int	all_ate;
	int	meals;

	while (get_stop(table) == 0)
	{
		i = 0;
		all_ate = 1;
		while (i < table->nb_philos)
		{
			if (get_meal_data(table, &meals, i))
				return (1);
			if (table->must_eat == -1 || meals < table->must_eat)
				all_ate = 0;
			i++;
		}
		if (table->must_eat != -1 && all_ate == 1)
		{
			set_stop(table, 1);
			return (0);
		}
		usleep(500);
	}
	return (0);
}
