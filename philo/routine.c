#include "includes/philo.h"

void    precise_sleep(long long duration_ms, t_table *table)
{
	long long	start;

	start = get_time_in_ms();
	while (get_stop(table) == 0)
	{
		if (get_time_in_ms() - start >= duration_ms)
			break ;
		usleep(500);
	}
}

void take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms(); 
	philo->meals_eaten++; 
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	precise_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void *single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	precise_sleep(philo->table->time_to_die, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void *routine(void *arg)
{
	t_philo * philo; 

	philo = (t_philo *)arg; 
	if (philo->table->nb_philos == 1)
		return (single_philo(philo));
	if (philo->id % 2 == 0)
		precise_sleep(philo->table->time_to_eat / 2, philo->table);
	while (get_stop(philo->table) == 0)
	{
		take_forks(philo);
		eat(philo);
		if (get_stop(philo->table))
			break ;
		print_state(philo, "is sleeping");
		precise_sleep(philo->table->time_to_sleep, philo->table);
		if (get_stop(philo->table))
			break ;
		print_state(philo, "is thinking");
		usleep(500);
	}
	return (NULL); 
}

int start_simulation(t_table *table)
{
	int i; 

	i = 0; 
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]) != 0)
		{
			set_stop(table, 1); 
			i = 0; 
			while (i < table->threads_created_count)
			{
				pthread_join(table->philos[i].thread, NULL); 
				i++;
			}
			return (1);
		}
		table->threads_created_count++;
		i++;
	}
	return (0); 
}
