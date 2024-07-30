/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roespici <roespici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:36:38 by roespici          #+#    #+#             */
/*   Updated: 2024/07/27 11:10:12 by roespici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	is_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
			continue ;
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	count_arg(int argc)
{
	if (argc < 5 || argc > 6)
	{
		if (argc < 5 && (5 - argc > 1))
			return (printf("%d arguments are missing\n", 5 - argc), FAILURE);
		else if (argc == 4)
			return (printf("1 argument is missing\n"), FAILURE);
		if (argc > 6 && (argc - 6 > 1))
			return (printf("There are %d arguments more than necessary\n", \
				argc - 6), FAILURE);
		else if (argc == 7)
			return (printf("There is 1 argument more than necessary\n"), \
				FAILURE);
	}
	return (SUCCESS);
}

static int	check_error(int argc, char **argv, int flag_error)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (is_numeric(argv[i]) == FAILURE)
		{
			printf("Argv[%d] is not a numeric value\n", i);
			flag_error = 1;
		}
		if (ft_atoi(argv[i]) < 0)
		{
			printf("Argv[%d] is not a positive value\n", i);
			flag_error = 1;
		}
		if (i >= 2 && i <= 4 && ft_atoi(argv[i]) < 60)
		{
			printf("Argv[%d] is too low\n", i);
			flag_error = 1;
		}
	}
	return (flag_error);
}

int	check_arg(int argc, char **argv)
{
	int	flag_error;

	flag_error = 0;
	if (count_arg(argc) == FAILURE)
		flag_error = 1;
	flag_error = check_error(argc, argv, flag_error);
	if (flag_error)
		return (FAILURE);
	return (SUCCESS);
}
