/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:57:14 by roespici          #+#    #+#             */
/*   Updated: 2024/08/02 12:02:53 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	finish_eating(t_table *table)
{
	int	i;
	int	nb_done_eating;

	nb_done_eating = 0;
	i = -1;
	while (++i < table->nb_philosophers)
	{
		pthread_mutex_lock(table->philo[i].last_meal_mutex);
		if (table->philo[i].nb_meal >= table->philo[i].have_to_eat)
			nb_done_eating++;
		pthread_mutex_unlock(table->philo[i].last_meal_mutex);
	}
	if (nb_done_eating == table->nb_philosophers)
	{
		pthread_mutex_lock(&table->simulation_running_mutex);
		table->simulation_running = STOP;
		pthread_mutex_unlock(&table->simulation_running_mutex);
		return (STOP);
	}
	return (RUN);
}

static void	monitor_sim(t_table *table)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->nb_philosophers)
		{
			if (handle_death(&table->philo[i]) == DEAD)
			{
				pthread_mutex_lock(&table->simulation_running_mutex);
				table->simulation_running = STOP;
				pthread_mutex_unlock(&table->simulation_running_mutex);
				return ;
			}
			if (table->philo->have_to_eat != -1)
				if (finish_eating(table) == STOP)
					return ;
		}
		usleep(100);
	}
}

static void	start_sim(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philosophers)
	{
		if (pthread_create(&table->philo[i].thread, NULL, philo_routine, \
			&table->philo[i]) != 0)
			return ;
	}
	monitor_sim(table);
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
		free_all(table);
		return (SUCCESS);
	}
	start_sim(table);
	i = -1;
	while (++i < table->nb_philosophers)
		pthread_join(table->philo[i].thread, NULL);
	free_all(table);
	return (SUCCESS);
}
