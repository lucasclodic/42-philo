/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:42:18 by lclodic           #+#    #+#             */
/*   Updated: 2026/02/25 15:55:20 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/philo.h"

int philo(t_table *table, char **argv)
{
	if (parsing_argv(argv, &table) != 0)
		return (1);
	if (init_table(&table) != 0)
	{
		cleanup(&table); 
		return (1); 
	}
	if (init_philos(&table) != 0)
	{
		cleanup(&table); 
		return (1); 
	}
	if (start_simulation(&table) != 0)
	{
		cleanup(&table); 
		return (1); 
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int i; 

	table = (t_table){0};
	if (argc != 5 && argc != 6)
		return (1);
	if (philo(table, argv) != 0)
		return (1);
	monitor_simulation(&table);
	i = 0;
	while (i < table.nb_philos)
	{
		pthread_join(table.philos[i].thread, NULL);
		i++;
	}
	cleanup(&table);
	return (0);
}
