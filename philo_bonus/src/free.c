/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:53:35 by roespici          #+#    #+#             */
/*   Updated: 2024/07/29 15:56:47 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_forks)
	{
		sem_close(*table->forks);
		sem_unlink("/fork");
	}
	sem_close(table->simulation_running_sem);
	sem_unlink("/simmulation");
	sem_close(table->last_meal_sem);
	sem_unlink("/last meal");
	sem_close(table->print_sem);
	sem_unlink("/print");
	free(table->philo);
	free(table->forks);
	free(table);
}
