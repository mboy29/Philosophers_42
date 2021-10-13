/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:31:22 by mboy              #+#    #+#             */
/*   Updated: 2021/10/08 10:31:25 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK       "has taken a fork"
# define EAT        "is eating"
# define SLEEP      "is sleeping"
# define THINK      "is thinking"
# define DEAD       "is dead"
# define OPTION     "must it counter reached"

typedef struct s_philo
{
	int				idx;
	int				option;
	pthread_t		t_id[2];
	int				forks[2];
	long long		time_meal;
	long long		time_limit;
	struct s_data	*data;
	pthread_mutex_t	m_eat;
}				t_philo;

typedef struct s_data
{
	int				amount;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tt_option;
	int				dead;
	int				option;
	long long		time_start;
	t_philo			*philo;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_option;
}				t_data;

t_data		*p_init_data(int ac, char **av);
int			p_init_check(t_data *data);
int			p_init_philo(t_data *data);
int			p_init_mutex(t_data *data);

int			p_exec_start(t_data *data);
void		*p_exec_routine(void *param);
void		*p_exec_dead(void *param);
int			p_exec_end(t_data *data);

int			p_status_dead(t_data *data);
int			p_status_option(t_data *data);
void		p_status_fork(t_philo *philo);
void		p_status_eat(t_philo *philo);
void		p_status_sleep_think(t_philo *philo);

long long	p_tool_time(void);
int			p_tool_atoi(char *str);
void		p_tool_status(t_philo *philo, char *mess);
int			p_tool_strcmp(const char *s1, const char *s2);

void		p_print_str(char *str);
void		p_print_nbr(long long nbr);
void		p_print_status(t_philo *philo, char *mess);

#endif