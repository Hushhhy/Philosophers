/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:50:47 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/14 15:29:58 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print_it(philo, FORK);
	pthread_mutex_lock(philo->fork_r);
	print_it(philo, FORK);
	if (death(philo->table))
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return ;
	}
	print_it(philo, EAT);
	pthread_mutex_lock(&philo->table->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->m_last_meal);
	ft_usleep(philo->table->eat_time, philo->table);
	if (!death(philo->table))
	{
		pthread_mutex_lock(&philo->table->m_meal);
		philo->count_meal++;
		pthread_mutex_unlock(&philo->table->m_meal);
	}
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	sleeping(t_philo *philo)
{
	if (death(philo->table))
		return ;
	print_it(philo, SLEEP);
	ft_usleep(philo->table->sleep_time, philo->table);
}

void	thinking(t_philo *philo)
{
	size_t	think_time;

	if (death(philo->table))
		return ;
	print_it(philo, THINK);
	if (philo->table->philos_nbr % 2 == 0)
		return ;
	else if (philo->table->sleep_time > philo->table->eat_time)
		return ;
	else
		think_time = 100;
	ft_usleep(think_time, philo->table);
}
