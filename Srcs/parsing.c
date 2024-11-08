/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:06:02 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/08 17:55:16 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_manager(int ac, t_table *table)
{
	if (table->philos_nbr < 1)
		return (ft_putstr_fd("Error: philo value must be at least 1\n", 2), 1);
	if (table->die_time < 60 || table->eat_time < 60 || table->sleep_time < 60)
		return (ft_putstr_fd("Error: time value must be at least 60\n", 2), 1);
	if (ac == 6 && table->must_eat < 1)
		return (ft_putstr_fd("Error: at least 1 philo need to eat\n", 2), 1);
	return (0);
}

int	arg_check(int ac, char **av)
{
	int	i;
	int	j;
	int	n;

	i = 1;
	while (i < ac)
	{
		j = 0;
		n = 0;
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]) || n > 10)
			{
				ft_putstr_fd("Error: wrong arguments format\n", 2);
				return (1);
			}
			j++;
			n++;
		}
		i++;
	}
	return (0);
}

int	parsing(int ac, char **av, t_table *table)
{
	int	stop;

	stop = 0;
	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("Error: needed 5 or 6 arguments\n", 2), 1);
	if (arg_check(ac, av))
		return (1);
	table->philos_nbr = ft_atol(av[1], &stop);
	table->die_time = ft_atol(av[2], &stop);
	table->eat_time = ft_atol(av[3], &stop);
	table->sleep_time = ft_atol(av[4], &stop);
	table->start = get_time() + table->philos_nbr * 10;
	if (ac == 6)
		table->must_eat = ft_atol(av[5], &stop);
	else
		table->must_eat = 0;
	if (stop)
		return (ft_putstr_fd("Error: wrong arguments values", 2), 1);
	if (error_manager(ac, &table))
		return (1);
	return (0);
}
