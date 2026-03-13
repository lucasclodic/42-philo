#include "includes/philo.h"

int get_meal_data(t_table *table, long long * last_meal, int * meals, int i)
{
	long long   now;

	pthread_mutex_lock(&table->philos[i].meal_mutex);
	*last_meal = table->philos[i].last_meal;
	*meals = table->philos[i].meals_eaten;
	pthread_mutex_unlock(&table->philos[i].meal_mutex);
	now = get_time_in_ms();
	if (now - *last_meal >= table->time_to_die)
	{
		set_stop(table, 1);
		pthread_mutex_lock(&table->print_mutex);
		printf("%lld %d died\n", now - table->start_time, table->philos[i].id);
		pthread_mutex_unlock(&table->print_mutex);
		return (1);
	}
	return (0);
}

int	monitor_simulation(t_table *table)
{
	int			i;
	int			all_ate;
	long long	last_meal;
	int			meals;

	while (get_stop(table) == 0)
	{
		i = 0;
		all_ate = 1;
		while (i < table->nb_philos)
		{
			if (get_meal_data(table, &last_meal, &meals, i))
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
