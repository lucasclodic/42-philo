/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:42:21 by lclodic           #+#    #+#             */
/*   Updated: 2026/04/02 15:57:11 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_table
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				forks_init_count;
	int				meal_mutex_init_count;
	int				threads_created_count;
	int				stop_mutex_init;
	int				print_mutex_init;
};

struct s_philo
{
	int				id;
	pthread_t		thread;
	t_table			*table;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	long long		last_meal;
	int				meals_eaten;
};

// init.c
int			init_table(t_table *table);
int			init_philos(t_table *table);
int			parsing_argv(char **argv, t_table *table);
int			start_simulation(t_table *table);

// utils.c
int			ft_atoi(char *str);
long long	get_time_in_ms(void);
int			is_valid_number(char *str);

// sync_utils.c
int			get_stop(t_table *table);
void		set_stop(t_table *table, int value);
void		print_state(t_philo *philo, char *msg);
void		cleanup(t_table *table);
void		precise_sleep(long long duration_ms, t_table *table);

// routine.c
void		*routine(void *arg);

// monitor.c
int			monitor_simulation(t_table *table);

#endif
