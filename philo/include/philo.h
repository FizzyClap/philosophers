/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:51:40 by roespici          #+#    #+#             */
/*   Updated: 2024/07/26 14:07:40 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>
# define SUCCESS 0
# define FAILURE -1
# define LIFE 0
# define DEAD 1
# define RUN 1
# define STOP 0

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*simulation_running_mutex;
	pthread_mutex_t	*last_meal_mutex;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				have_to_eat;
	long long		last_meal;
	long long		start_time;
	int				nb_meal;
	int				*is_dead;
	int				*simulation_running;
	int				nb_philo;
	int				is_eating;
	int				hold_fork;
}	t_philo;

typedef struct s_table
{
	int				nb_philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	simulation_running_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_meal_mutex;
	int				nb_forks;
	int				simulation_running;
	int				is_dead;
	int				nb_finish_eating;
	int				have_to_eat;
	t_philo			*philo;
}	t_table;

//PARSING
int			check_arg(int argc, char **argv);
int			ft_atoi(const char *nptr);
//INIT
void		init_table(t_table *table, char **argv);
void		init_philo(t_table *table, t_philo *philo, int argc, char **argv);
//ROUTINE
void		*philo_routine(void *arg);
long long	get_current_time(void);
void		print_message(t_philo *philo, const char *msg);
int			handle_death(t_philo *philo);
int			simulation_status(t_philo *philo);
int			ft_usleep(t_philo *philo, int time_to);
//MEMORY
void		free_all(t_table *table);

#endif
