/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:42:18 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/philo.h"

static void	take_forks_and_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "has taken a fork");
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	precise_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	think(t_philo *philo)
{
	long long	think_time;

	print_state(philo, "is thinking");
	if (philo->table->nb_philos % 2 == 0)
		think_time = philo->table->time_to_eat
			- philo->table->time_to_sleep;
	else
		think_time = philo->table->time_to_eat * 2
			- philo->table->time_to_sleep - 1;
	if (think_time > 0)
		precise_sleep(think_time, philo->table);
}

static void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	precise_sleep(philo->table->time_to_die, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_philos == 1)
		return (single_philo(philo));
	if (philo->id % 2 == 0)
		precise_sleep(philo->table->time_to_eat / 2, philo->table);
	while (get_stop(philo->table) == 0)
	{
		take_forks_and_eat(philo);
		if (get_stop(philo->table))
			break ;
		print_state(philo, "is sleeping");
		precise_sleep(philo->table->time_to_sleep, philo->table);
		if (get_stop(philo->table))
			break ;
		think(philo);
	}
	return (NULL);
}
