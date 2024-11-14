/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:58:14 by acarpent          #+#    #+#             */
/*   Updated: 2024/11/14 16:38:27 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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

# define YELLOW "\033[33m"
# define RED "\033[0;31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"

/*---------------------MAIN------------------------*/

int		main(int ac, char **av);

/*----------------------UTILS----------------------*/

void	print_it(t_philo *philo, int msg);
void	end_clean(t_table *table);

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
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);

/*-----------------TIME FUNCTIONS------------------*/

void	ft_usleep(size_t time, t_table *table);
size_t	get_time(void);

/*-------------SIMULATION FUNCTIONS----------------*/

int		simulation(t_table *table);
void	*philo_routine(void *arg);
void	wait_philos(size_t start);

/*-------------------ACTIONS-----------------------*/

int		death_check(t_philo *philo);
void	death_set(t_table *table);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	*death_handle(void *arg);
void	eating(t_philo *philo);
int		ending(t_table *table);
int		death(t_table *table);

#endif