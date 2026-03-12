#include "includes/philo.h"

int init_table(t_table *table)
{
	int i; 

	table->start_time = get_time_in_ms();
	table->stop = 0; 
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1); 
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	table->philos = malloc(sizeof(t_philo) * table->nb_philos); 
	if (!table->philos)
		return (1); 
	return (0);
}

int init_philos(t_table *table)
{
	int i; 

	i = 0; 
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philos];
		if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0)
			return (1);
		table->philos[i].last_meal = table->start_time;
		table->philos[i].meals_eaten = 0;
		i++;
	}
	return (0);
}