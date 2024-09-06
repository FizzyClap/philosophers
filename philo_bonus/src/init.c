/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:10:58 by roespici          #+#    #+#             */
/*   Updated: 2024/09/06 17:30:55 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	create_semaphore(t_table *table)
{
	sem_unlink("state");
	table->state_sem = sem_open("state", O_CREAT, 0644, 0);
	if (table->state_sem == SEM_FAILED)
		return ;
	sem_unlink("dead");
	table->dead_sem = sem_open("dead", O_CREAT, 0644, 1);
	if (table->dead_sem == SEM_FAILED)
		return ;
	sem_unlink("print");
	table->print_sem = sem_open("print", O_CREAT, 0644, 1);
	if (table->print_sem == SEM_FAILED)
		return ;
	sem_unlink("simmulation");
	table->simulation_sem = sem_open("simmulation", O_CREAT, 0644, 1);
	if (table->simulation_sem == SEM_FAILED)
		return ;
	sem_unlink("meal count");
	table->meal_count_sem = sem_open("meal count", O_CREAT, 0644, 0);
	if (table->meal_count_sem == SEM_FAILED)
		return ;
	sem_unlink("priority");
	table->priority_sem = sem_open("priority", O_CREAT, 0644, 1);
	if (table->priority_sem == SEM_FAILED)
		return ;
}

void	init_table(t_table *table, char **argv)
{
	table->nb_philosophers = ft_atoi(argv[1]);
	table->philo = malloc(sizeof(t_philo) * table->nb_philosophers);
	if (!table->philo)
		return ;
	table->monitor = malloc(sizeof(pthread_t) * table->nb_philosophers);
	if (!table->monitor)
		return ;
	table->nb_forks = table->nb_philosophers;
	sem_unlink("forks");
	table->forks_sem = sem_open("forks", O_CREAT, 0644, table->nb_forks);
	if (table->forks_sem == SEM_FAILED)
		return ;
	sem_unlink("last meal");
	table->last_meal_sem = sem_open("last meal", O_CREAT, 0644, 1);
	if (table->last_meal_sem == SEM_FAILED)
		return ;
	table->is_dead = ALIVE;
	create_semaphore(table);
}

static void	init_semaphore(t_table *table, t_philo *philo, int i)
{
	philo[i].forks_sem = table->forks_sem;
	philo[i].last_meal_sem = table->last_meal_sem;
	philo[i].state_sem = table->state_sem;
	philo[i].dead_sem = table->dead_sem;
	philo[i].print_sem = table->print_sem;
	philo[i].simulation_sem = table->simulation_sem;
	philo[i].meal_count_sem = table->meal_count_sem;
	philo[i].priority_sem = table->priority_sem;
}

void	init_philo(t_table *table, t_philo *philo, int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < table->nb_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].have_to_eat = -1;
		if (argc == 6)
			philo[i].have_to_eat = ft_atoi(argv[5]);
		philo[i].start_time = get_current_time();
		philo[i].last_meal = philo[i].start_time;
		philo[i].nb_philo = table->nb_philosophers;
		philo[i].is_eating = 0;
		philo[i].hold_fork = 0;
		philo[i].is_dead = &table->is_dead;
		init_semaphore(table, philo, i);
	}
}
