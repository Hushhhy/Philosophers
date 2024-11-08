/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:58:14 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/08 18:14:50 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_table
{
	t_philo			*philos;
	pthread_t		death_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_last_meal;
	size_t			philos_nbr;
	size_t			start;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			must_eat;
	int				dead;
}	t_table;

typedef struct s_philo
{
	size_t			id;
	size_t			pos;
	size_t			thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	long long		last_meal;
	t_table			*table;
	size_t			count_meal;
}	t_philo;

enum
{
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	DEAD = 4,
	FORK = 5
};

/*----------------PARSING FUNCTIONS----------------*/

int		parsing(int ac, char **av, t_table *table);
int		error_manager(int ac, t_table *table);
int		arg_check(int ac, char **av);

/*-----------------INIT FUNCTIONS------------------*/

void	philo_forks_init(t_philo *philo, size_t i);
int		init_philos(t_table *table);
int		init_forks(t_table *table);
int		init_table(t_table *table);
int		init_mutex(t_table *table);

/*----------------LIBRARY FUNCTIONS----------------*/

long	ft_atol(const char *str, int *stop);
void	ft_putstr_fd(char *s, int fd);
size_t  ft_strlen(const char *s);
int		ft_isdigit(int c);

/*-----------------TIME FUNCTIONS------------------*/

size_t	get_time(void);

/*-------------SIMULATION FUNCTIONS----------------*/



#endif