/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:04:36 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/14 15:26:23 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (parsing(ac, av, &table))
		return (1);
	if (init_table(&table))
		return (1);
	if (init_mutex(&table))
		return (1);
	if (simulation(&table))
		return (1);
	return (0);
}
