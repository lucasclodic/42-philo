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



int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (1);
	if (parsing_argv(argv, &table) == 0)
	{
		if (!init_table(&table) && !init_philos(&table))
		{
			int i = 0; 
			while (i < table.nb_philos)
			{
				printf("Philo numéro %d\n", table.philos[i].id);
				printf("Adresse fork gauche %p\n", table.philos[i].left_fork);
				printf("Adresse fork droite %p\n", table.philos[i].right_fork);
				printf("======================\n");
				i++; 
			}
		}
		return (0);
	}
	return (1); 
}
