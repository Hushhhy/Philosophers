/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:57:12 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/14 15:27:17 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_forks_init(t_philo *philo, size_t i)
{
	if (philo->pos % 2)
	{
		philo->fork_l = &philo->table->forks[i];
		philo->fork_r = &philo->table->forks[(i + 1)
			% philo->table->philos_nbr];
	}
	else
	{
		philo->fork_r = &philo->table->forks[i];
		philo->fork_l = &philo->table->forks[(i + 1)
			% philo->table->philos_nbr];
	}
}

int	init_forks(t_table *table)
{
	size_t	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos_nbr);
	if (!table->forks)
	{
		free(table->philos);
		return (1);
	}
	i = 0;
	while (i < table->philos_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			free(table->philos);
			free(table->forks);
			return (1);
		}
		philo_forks_init(&table->philos[i], i);
		i++;
	}
	return (0);
}

int	init_philos(t_table *table)
{
	size_t	i;

	table->philos = malloc(sizeof(t_philo) * table->philos_nbr);
	if (!table->philos)
		return (1);
	i = 0;
	memset(table->philos, 0, sizeof(t_philo) * table->philos_nbr);
	while (i < table->philos_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].pos = i + 1;
		table->philos[i].table = table;
		table->philos[i].count_meal = 0;
		i++;
	}
	return (0);
}

int	init_table(t_table *table)
{
	if (init_philos(table) || init_forks(table))
		return (1);
	table->dead = 0;
	return (0);
}

int	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->m_dead, NULL))
		return (1);
	if (pthread_mutex_init(&table->m_meal, NULL))
		return (1);
	if (pthread_mutex_init(&table->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&table->m_last_meal, NULL))
		return (1);
	return (0);
}
