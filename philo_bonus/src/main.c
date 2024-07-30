/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:45:24 by roespici          #+#    #+#             */
/*   Updated: 2024/07/30 16:27:57 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	finish_eating(t_table *table)
{
	int	nb_done_eating;
	int	i;

	nb_done_eating = 0;
	i = -1;
	while (++i < table->nb_philosophers)
	{
		sem_wait(table->philo->last_meal_sem);
		if (table->philo[i].nb_meal >= table->philo[i].have_to_eat)
			nb_done_eating++;
		sem_post(table->philo->last_meal_sem);
	}
	if (nb_done_eating == table->nb_philosophers)
	{
		sem_wait(table->simulation_running_sem);
		table->simulation_running = STOP;
		sem_post(table->simulation_running_sem);
		return (STOP);
	}
	return (RUN);
}

static void	*monitor_sim(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = -1;
		while (++i < table->nb_philosophers)
		{
			if (handle_death(&table->philo[i]) == DEAD)
			{
				sem_wait(table->simulation_running_sem);
				table->simulation_running = STOP;
				sem_post(table->simulation_running_sem);
				return (NULL);
			}
			if (table->philo->have_to_eat != -1)
				if (finish_eating(table) == STOP)
					return (NULL);
		}
		usleep(100);
	}
	return (NULL);
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
	i = -1;
	while (++i < table->nb_philosophers)
	{
		table->philo[i].process = fork();
		if (table->philo[i].process == -1)
			return (FAILURE);
		else if (table->philo[i].process == 0)
		{
			if (pthread_create(&table->philo[i].thread, NULL, monitor_sim, &table->philo[i]))
				exit(EXIT_FAILURE);
			philo_routine(&table->philo[i]);
			pthread_join(table->philo[i].thread, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	i = -1;
	while (++i < table->nb_philosophers)
		waitpid(table->philo[i].process, NULL, 0);
		//kill(table->philo[i].process, SIGKILL);
	free_all(table);
}
