/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:40:14 by roespici          #+#    #+#             */
/*   Updated: 2024/07/30 14:21:58 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	simulation_status(t_philo *philo)
{
	int	status;

	sem_wait(philo->simulation_running_sem);
	status = *(philo->simulation_running);
	sem_post(philo->simulation_running_sem);
	return (status);
}

static void	release_forks(t_philo *philo)
{
	sem_post(philo->left_fork_sem);
	sem_post(philo->right_fork_sem);
}

static int	take_forks(t_philo *philo)
{
	if (philo->nb_philo > 1)
	{
		sem_wait(philo->left_fork_sem);
		if (simulation_status(philo) == STOP)
		{
			sem_post(philo->left_fork_sem);
			return (STOP);
		}
		print_message(philo, "has taken a fork");
		philo->hold_fork++;
	}
	sem_wait(philo->right_fork_sem);
	if (simulation_status(philo) == STOP)
	{
		release_forks(philo);
		return (STOP);
	}
	print_message(philo, "has taken a fork");
	philo->hold_fork++;
	return (RUN);
}

static int	handle_eat(t_philo *philo)
{
	if (take_forks(philo) == STOP)
		return (STOP);
	if (philo->nb_philo == 1)
	{
		usleep(philo->time_to_die * 1000);
		sem_post(philo->right_fork_sem);
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
		philo->hold_fork = 0;
		sem_wait(philo->last_meal_sem);
		philo->is_eating = 0;
		philo->nb_meal++;
		sem_post(philo->last_meal_sem);
	}
	return (RUN);
}

void	*philo_routine(t_philo *philo)
{
	while (1)
	{
		if (simulation_status(philo) == STOP)
			break ;
		print_message(philo, "is thinking");
		if (handle_eat(philo) == STOP)
			break ;
		if (simulation_status(philo) == STOP)
			break ;
		print_message(philo, "is sleeping");
		if (ft_usleep(philo, philo->time_to_sleep) == STOP)
			break ;
	}
	return (NULL);
}
