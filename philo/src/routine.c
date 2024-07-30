/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:46:13 by roespici          #+#    #+#             */
/*   Updated: 2024/07/30 09:10:29 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	simulation_status(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->simulation_running_mutex);
	status = *(philo->simulation_running);
	pthread_mutex_unlock(philo->simulation_running_mutex);
	return (status);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(philo->right_fork_mutex);
}

static int	take_forks(t_philo *philo)
{
	if (philo->nb_philo > 1)
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		if (simulation_status(philo) == STOP)
			return (pthread_mutex_unlock(philo->left_fork_mutex), STOP);
		print_message(philo, "has taken a fork");
		philo->hold_fork++;
	}
	pthread_mutex_lock(philo->right_fork_mutex);
	if (simulation_status(philo) == STOP)
		return (release_forks(philo), STOP);
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
		pthread_mutex_unlock(philo->right_fork_mutex);
	}
	if (philo->hold_fork == 2)
	{
		pthread_mutex_lock(philo->last_meal_mutex);
		philo->last_meal = get_current_time();
		philo->is_eating = 1;
		pthread_mutex_unlock(philo->last_meal_mutex);
		print_message(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		release_forks(philo);
		philo->hold_fork = 0;
		pthread_mutex_lock(philo->last_meal_mutex);
		philo->is_eating = 0;
		philo->nb_meal++;
		pthread_mutex_unlock(philo->last_meal_mutex);
	}
	return (RUN);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
