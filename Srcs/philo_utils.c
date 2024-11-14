/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:16:50 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/14 16:38:19 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_it(t_philo *philo, int msg)
{
	pthread_mutex_lock(&philo->table->m_print);
	if (death(philo->table) && msg != DEAD)
	{
		pthread_mutex_unlock(&philo->table->m_print);
		return ;
	}
	if (msg == DEAD)
	{
		printf("%s%09zu %zu died%s\n", RED,
			get_time() - philo->table->start, philo->id, RESET);
		death_set(philo->table);
	}
	else if (msg == EAT)
		printf("%s%09zu %zu is eating%s\n", GREEN,
			get_time() - philo->table->start, philo->id, RESET);
	else if (msg == SLEEP)
		printf("%s%09zu %zu is sleeping%s\n", BLUE,
			get_time() - philo->table->start, philo->id, RESET);
	else if (msg == THINK)
		printf("%s%09zu %zu is thinking%s\n", YELLOW,
			get_time() - philo->table->start, philo->id, RESET);
	else if (msg == FORK)
		printf("%s%09zu %zu has taken a fork%s\n", CYAN,
			get_time() - philo->table->start, philo->id, RESET);
	pthread_mutex_unlock(&philo->table->m_print);
}

void	end_clean(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->m_dead);
	pthread_mutex_destroy(&table->m_meal);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_last_meal);
}
