#include "includes/philo.h"

int	get_stop(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->stop_mutex);
	stop = table->stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return (stop);
}

void	set_stop(t_table *table, int value)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop = value;
	pthread_mutex_unlock(&table->stop_mutex);
}

void print_state(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (get_stop(philo->table) == 0)
		printf("%lld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id, msg); 
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void cleanup(t_table *table)
{
	int i; 

	i = 0; 
	while (i < table->forks_init_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++; 
	}
	i = 0; 
	while (i < table->meal_mutex_init_count)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	if (table->stop_mutex_init)
		pthread_mutex_destroy(&table->stop_mutex); 
	if (table->print_mutex_init)
		pthread_mutex_destroy(&table->print_mutex);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos); 
}
