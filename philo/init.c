#include "includes/philo.h"

int	parsing_argv(char **argv, t_table *table)
{
	int i; 

	i = 1; 
	while (argv[i])
	{
		if (is_valid_number(argv[i]) == 1 || ft_atoi(argv[i]) < 1)
			return (1);
		i++;
	}
	table->nb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	return (0);
}

int init_table(t_table *table)
{
	int i; 

	table->start_time = get_time_in_ms();
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1); 
	table->stop_mutex_init = 1;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	table->print_mutex_init = 1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		table->forks_init_count++;
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
		table->meal_mutex_init_count++;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].meals_eaten = 0;
		i++;
	}
	return (0);
}
