/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 14:10:13 by roespici          #+#    #+#             */
/*   Updated: 2024/10/02 09:39:09 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	*monitor_sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (handle_death(philo) == DEAD)
		{
			sem_wait(philo->dead_sem);
			print_message(philo, "died");
			philo->is_dead = DEAD;
			sem_post(philo->state_sem);
			return (NULL);
		}
		sem_wait(philo->last_meal_sem);
		if (philo->have_to_eat == 0 && philo->id == philo->nb_philo)
		{
			sem_wait(philo->dead_sem);
			sem_post(philo->state_sem);
			sem_post(philo->last_meal_sem);
			return (NULL);
		}
		sem_post(philo->last_meal_sem);
		usleep(100);
	}
	return (NULL);
}

static void	start_children(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philosophers)
	{
		table->philo[i].process = fork();
		if (table->philo[i].process < 0)
			return ;
		else if (table->philo[i].process == 0)
		{
			if (pthread_create(&table->monitor[i], NULL, monitor_sim, \
				&table->philo[i]))
				exit(EXIT_FAILURE);
			philo_routine(&table->philo[i]);
			pthread_join(table->monitor[i], NULL);
			exit(EXIT_SUCCESS);
		}
	}
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		i;

	if (check_arg(argc, argv) == FAILURE)
		return (FAILURE);
	table = malloc(sizeof(t_table));
	if (!table)
		return (FAILURE);
	init_table(table, argv);
	init_philo(table, table->philo, argc, argv);
	if (table->philo->have_to_eat == 0)
	{
		printf("The number of meal necessary is 0, so every Philosophers ");
		printf("came at the table for nothing and come back home safe.\n");
		close_semaphore(table);
		free_all(table);
		return (SUCCESS);
	}
	start_children(table);
	i = -1;
	sem_wait(table->state_sem);
	while (++i < table->nb_philosophers)
		kill(table->philo[i].process, SIGKILL);
	close_semaphore(table);
	free_all(table);
}
