/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lclodic <lclodic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:42:21 by lclodic           #+#    #+#             */
/*   Updated: 2026/02/25 15:57:11 by lclodic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_table t_table;
typedef struct s_philo t_philo;

struct s_table
{
	// ==== argv ====
	int nb_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat; // le nombre de fois que chaque philo doit manger (facultatif)

	// ==== infos ====
	long long start_time; // long long car gettimeofday() donne un très grand nombre
	int stop; // 0 tant que la simulation continue et 1 dès qu'un philosphe meurt, lu par les philo et modifié par le monitor

	pthread_mutex_t stop_mutex; // mutex stop car il est lu par les philo et modifié par le monitor donc pour ne pas lire et modifier en même temps (data races) on place un mutex
	pthread_mutex_t print_mutex; // éviter que deux threads écrivent en même temps dans le terminal
	pthread_mutex_t *forks; // tableau de mutex de fourchettes

	t_philo *philos; // tableau de tous les philos
};

struct s_philo
{
	int id; 
	pthread_t thread; // identifiant du thread du philo, sert à créer suivre et attendre ce thread
	t_table *table; // pointeur vers la table partagée

	pthread_mutex_t *left_fork; // pour un philo[i] ce sera la fork[i]
	pthread_mutex_t *right_fork; // pour un philo[i] ce sera la fork[(i + 1) % N]
	pthread_mutex_t meal_mutex; // mutex de verrou pour last_meal et meals_eaten car monitor le lit et philo le modifie après chaque repas

	long long last_meal; // c'est propre à un philo mais le thread du philo les écrit et le thread monitor le lit
	int meals_eaten; // pareil ici donc il faut protéger avec soit un mutex par philo ou un mutex global d'état (?)

};

// init.c
int init_table(t_table *table);
int init_philos(t_table *table);

// utils.c
int			ft_atoi(char *str);
long long	get_time_in_ms(void);
int			is_valid_number(char *str);

// sync_utils.c
int			get_stop(t_table *table);
void		set_stop(t_table *table, int value);
void		print_state(t_philo *philo, char *msg);
void		cleanup(t_table *table);

// routine.c
void    precise_sleep(long long duration_ms, t_table *table);
void	*routine(void *arg);
int		start_simulation(t_table *table); 
int		monitor_simulation(t_table *table);

#endif