/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:24:29 by roespici          #+#    #+#             */
/*   Updated: 2024/08/02 12:40:46 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	release_forks(t_philo *philo)
{
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
	philo->hold_fork = 0;
}

static int	take_forks(t_philo *philo)
{
	sem_wait(philo->priority_sem);
	if (philo->nb_philo > 1)
	{
		sem_wait(philo->forks_sem);
		print_message(philo, "has taken a fork");
		philo->hold_fork++;
	}
	sem_wait(philo->forks_sem);
	print_message(philo, "has taken a fork");
	philo->hold_fork++;
	sem_post(philo->priority_sem);
	return (RUN);
}

static int	handle_eat(t_philo *philo)
{
	if (take_forks(philo) == STOP)
		return (STOP);
	if (philo->nb_philo == 1)
	{
		usleep(philo->time_to_die * 1000);
		sem_post(philo->forks_sem);
		return (STOP);
	}
	if (philo->hold_fork == 2)
	{
		sem_wait(philo->last_meal_sem);
		philo->last_meal = get_current_time();
		philo->is_eating = 1;
		sem_post(philo->last_meal_sem);
		print_message(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		release_forks(philo);
		sem_wait(philo->last_meal_sem);
		philo->is_eating = 0;
		if (philo->have_to_eat != -1)
			philo->have_to_eat--;
		sem_post(philo->last_meal_sem);
	}
	return (RUN);
}

void	*philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		print_message(philo, "is thinking");
		if (handle_eat(philo) == STOP)
			break ;
		print_message(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
	}
	return (NULL);
}
