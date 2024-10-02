/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:43:11 by roespici          #+#    #+#             */
/*   Updated: 2024/10/02 09:40:41 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <pthread.h>

# define SUCCESS 0
# define FAILURE -1
# define ALIVE 0
# define DEAD 1
# define RUN 1
# define STOP 0
# define NO 0
# define YES 1

typedef struct s_philo
{
	int			id;
	sem_t		*forks_sem;
	sem_t		*print_sem;
	sem_t		*state_sem;
	sem_t		*dead_sem;
	sem_t		*last_meal_sem;
	sem_t		*meal_count_sem;
	sem_t		*simulation_sem;
	sem_t		*priority_sem;
	pid_t		process;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			have_to_eat;
	long long	last_meal;
	long long	start_time;
	int			nb_philo;
	int			is_eating;
	int			hold_fork;
	int			is_dead;
}	t_philo;

typedef struct s_table
{
	int			nb_philosophers;
	pthread_t	*monitor;
	sem_t		*forks_sem;
	sem_t		*state_sem;
	sem_t		*dead_sem;
	sem_t		*print_sem;
	sem_t		*last_meal_sem;
	sem_t		*meal_count_sem;
	sem_t		*simulation_sem;
	sem_t		*priority_sem;
	int			nb_forks;
	t_philo		*philo;
}	t_table;

//PARSING
int			check_arg(int argc, char **argv);
int			ft_atoi(const char *nptr);
//INIT
void		init_table(t_table *table, char **argv);
void		init_philo(t_table *table, t_philo *philo, int argc, char **argv);
//ROUTINE
long long	get_current_time(void);
void		*philo_routine(t_philo *philo);
void		print_message(t_philo *philo, const char *msg);
int			handle_death(t_philo *philo);
//FREE
void		free_all(t_table *table);
void		close_semaphore(t_table *table);
#endif
