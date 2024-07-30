/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:51:14 by roespici          #+#    #+#             */
/*   Updated: 2024/07/30 16:36:11 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_message(t_philo *philo, const char *msg)
{
	sem_wait(philo->print_sem);
	printf("%lld %d %s\n", get_current_time() - philo->start_time, \
			philo->id, msg);
	sem_post(philo->print_sem);
}

int	handle_death(t_philo *philo)
{
	sem_wait(philo->last_meal_sem);
	if (get_current_time() - philo->last_meal >= philo->time_to_die && \
		!philo->is_eating)
	{
		if (*(philo->is_dead) == LIFE)
		{
			print_message(philo, "died");
			*(philo->is_dead) = DEAD;
		}
		sem_post(philo->last_meal_sem);
		return (DEAD);
	}
	sem_post(philo->last_meal_sem);
	return (LIFE);
}

int	ft_usleep(t_philo *philo, int time_to)
{
	int	i;

	i = -1;
	while (++i < 10)
	{
		usleep(time_to * 100);
		if (simulation_status(philo) == STOP)
			return (STOP);
	}
	return (RUN);
}
