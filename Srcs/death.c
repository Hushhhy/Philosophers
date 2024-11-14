/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:51:10 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/14 15:28:56 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	death_set(t_table *table)
{
	pthread_mutex_lock(&table->m_dead);
	table->dead = 1;
	pthread_mutex_unlock(&table->m_dead);
}

int	death_check(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->m_last_meal);
	time = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->table->m_last_meal);
	if (time >= philo->table->die_time)
	{
		death_set(philo->table);
		usleep(1000);
		print_it(philo, DEAD);
		return (1);
	}
	return (0);
}

int	ending(t_table *table)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = 1;
	while (i < table->philos_nbr)
	{
		if (death_check(&table->philos[i]))
			return (1);
		if (table->must_eat)
		{
			pthread_mutex_lock(&table->m_meal);
			if (table->philos[i].count_meal < table->must_eat)
				ret = 0;
			pthread_mutex_unlock(&table->m_meal);
		}
		i++;
	}
	if (table->must_eat && ret)
	{
		death_set(table);
		return (1);
	}
	return (0);
}

int	death(t_table *table)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->m_dead);
	if (table->dead)
		ret = 1;
	pthread_mutex_unlock(&table->m_dead);
	return (ret);
}

void	*death_handle(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	wait_philos(table->start);
	while (!death(table))
	{
		if (ending(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
