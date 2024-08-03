/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:48:06 by roespici          #+#    #+#             */
/*   Updated: 2024/07/31 16:03:15 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_table(t_table *table, char **argv)
{
	int	i;

	table->nb_philosophers = ft_atoi(argv[1]);
	table->philo = malloc(sizeof(t_philo) * (table->nb_philosophers));
	if (!table->philo)
		return ;
	table->nb_forks = table->nb_philosophers;
	table->forks = malloc(sizeof(pthread_mutex_t) * (table->nb_forks));
	if (!table->forks)
		return ;
	i = -1;
	while (++i < table->nb_forks)
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return ;
	if (pthread_mutex_init(&table->simulation_running_mutex, NULL) != 0)
		return ;
	table->simulation_running = RUN;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return ;
	table->is_dead = ALIVE;
	if (pthread_mutex_init(&table->last_meal_mutex, NULL) != 0)
		return ;
	table->nb_finish_eating = 0;
}

static void	init_mutex(t_table *table, t_philo *philo, int i)
{
	void	*tmp;

	philo[i].left_fork_mutex = &table->forks[i];
	philo[i].right_fork_mutex = &table->forks[(i + 1) % table->nb_forks];
	if (i % 2 == 0)
	{
		tmp = philo[i].left_fork_mutex;
		philo[i].left_fork_mutex = philo[i].right_fork_mutex;
		philo[i].right_fork_mutex = tmp;
	}
	philo[i].simulation_running_mutex = &table->simulation_running_mutex;
	philo[i].print_mutex = &table->print_mutex;
	philo[i].last_meal_mutex = &table->last_meal_mutex;
}

void	init_philo(t_table *table, t_philo *philo, int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < table->nb_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].nb_philo = table->nb_philosophers;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].have_to_eat = -1;
		if (argc == 6)
			philo[i].have_to_eat = ft_atoi(argv[5]);
		philo[i].start_time = get_current_time();
		philo[i].nb_meal = 0;
		philo[i].last_meal = philo[i].start_time;
		philo[i].hold_fork = 0;
		philo[i].is_eating = 0;
		philo[i].is_dead = &table->is_dead;
		philo[i].simulation_running = &table->simulation_running;
		init_mutex(table, philo, i);
	}
}
