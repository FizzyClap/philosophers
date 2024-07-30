/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:17:52 by roespici          #+#    #+#             */
/*   Updated: 2024/07/30 15:08:15 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	create_semaphore(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_forks)
	{
		sem_unlink("/fork");
		table->forks[i] = sem_open("/fork", O_CREAT, 0644, 1);
		if (table->forks[i] == SEM_FAILED)
			return ;
	}
	sem_unlink("/simmulation");
	table->simulation_running_sem = sem_open("/simmulation", O_CREAT, 0644, 1);
	if (table->simulation_running_sem == SEM_FAILED)
		return ;
	sem_unlink("/last meal");
	table->last_meal_sem = sem_open("/last meal", O_CREAT, 0644, 1);
	if (table->last_meal_sem == SEM_FAILED)
		return ;
	sem_unlink("/print");
	table->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (table->print_sem == SEM_FAILED)
		return ;
}

void	init_table(t_table *table, char **argv)
{
	table->nb_philosophers = ft_atoi(argv[1]);
	table->philo = malloc(sizeof(t_philo) * table->nb_philosophers);
	if (!table->philo)
		return ;
	table->nb_forks = table->nb_philosophers;
	table->forks = malloc(sizeof(sem_t *) * table->nb_forks);
	if (!table->forks)
		return ;
	create_semaphore(table);
	table->simulation_running = RUN;
	table->nb_finish_eating = 0;
	table->is_dead = LIFE;
}

void	init_semaphore(t_table *table, t_philo *philo, int i)
{
	void	*tmp;

	philo[i].left_fork_sem = table->forks[i];
	philo[i].right_fork_sem = table->forks[(i + 1) % table->nb_forks];
	if (i % 2 == 0)
	{
		tmp = philo[i].left_fork_sem;
		philo[i].left_fork_sem = philo[i].right_fork_sem;
		philo[i].right_fork_sem = tmp;
	}
	philo[i].last_meal_sem = table->last_meal_sem;
	philo[i].print_sem = table->print_sem;
	philo[i].simulation_running_sem = table->simulation_running_sem;
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
		philo[i].nb_meal = 0;
		philo[i].nb_philo = table->nb_philosophers;
		philo[i].is_eating = 0;
		philo[i].hold_fork = 0;
		philo[i].is_dead = &table->is_dead;
		philo[i].simulation_running = &table->simulation_running;
		init_semaphore(table, philo, i);
	}
}
