/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:42:18 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/02 10:59:05 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/philo.h"

static int	run_simulation(t_table *table)
{
	int	i;

	if (init_table(table) != 0)
		return (1);
	if (init_philos(table) != 0)
		return (1);
	if (start_simulation(table) != 0)
		return (1);
	monitor_simulation(table);
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		ret;

	table = (t_table){0};
	if (argc != 5 && argc != 6)
		return (1);
	if (parsing_argv(argv, &table) != 0)
		return (1);
	ret = run_simulation(&table);
	cleanup(&table);
	return (ret);
}
