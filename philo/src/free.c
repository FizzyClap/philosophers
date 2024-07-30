/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:51:56 by roespici          #+#    #+#             */
/*   Updated: 2024/07/26 12:41:12 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_forks)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->simulation_running_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->last_meal_mutex);
	free(table->philo);
	free(table->forks);
	free(table);
}
