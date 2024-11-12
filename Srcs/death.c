/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:51:10 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/12 17:04:24 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		death(t_table *table)
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
	wait_philo(table->start);
	while (!death_time(table))
	{
		if (ending(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}