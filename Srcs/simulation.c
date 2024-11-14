/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:13:58 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/14 15:28:38 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->m_last_meal);
	philo->last_meal = philo->table->start;
	pthread_mutex_unlock(&philo->table->m_last_meal);
	wait_philos(philo->table->start);
	if (philo->table->philos_nbr == 1)
	{
		ft_usleep(philo->table->die_time, philo->table);
		if (!death(philo->table))
			print_it(philo, DEAD);
		return (NULL);
	}
	if (philo->pos % 2)
		ft_usleep(philo->table->eat_time, philo->table);
	while (!death(philo->table))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	simulation(t_table *table)
{
	size_t	i;

	i = 0;
	table->start = get_time() + (table->philos_nbr * 20);
	while (i < table->philos_nbr)
	{
		table->philos[i].last_meal = table->start;
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine,
				&table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&table->death_thread, NULL, &death_handle, table))
		return (1);
	i = 0;
	while (i < table->philos_nbr)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(table->death_thread, NULL))
		return (1);
	return (0);
}

void	wait_philos(size_t start)
{
	while (get_time() < start)
		continue ;
}
