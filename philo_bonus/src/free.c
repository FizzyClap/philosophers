/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:17:21 by roespici          #+#    #+#             */
/*   Updated: 2024/08/02 12:24:21 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	close_semaphore(t_table *table)
{
	sem_close(table->forks_sem);
	sem_unlink("forks");
	sem_close(table->last_meal_sem);
	sem_unlink("last meal");
	sem_close(table->state_sem);
	sem_unlink("state");
	sem_close(table->print_sem);
	sem_unlink("print");
	sem_close(table->dead_sem);
	sem_unlink("dead");
	sem_close(table->simulation_sem);
	sem_unlink("simmulation");
	sem_close(table->meal_count_sem);
	sem_unlink("meal count");
	sem_close(table->priority_sem);
	sem_unlink("priority");
}

void	free_all(t_table *table)
{
	free(table->philo);
	free(table->monitor);
	free(table);
}
