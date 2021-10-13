/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:31:31 by mboy              #+#    #+#             */
/*   Updated: 2021/10/08 10:31:32 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

void	*p_exec_dead(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		pthread_mutex_lock(&philo->m_eat);
		if (philo->time_limit > 0 && philo->time_limit < p_tool_time())
		{
			pthread_mutex_lock(&philo->data->m_dead);
			p_tool_status(philo, DEAD);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->m_dead);
			pthread_mutex_unlock(&philo->m_eat);
			return ((void *)1);
		}
		pthread_mutex_unlock(&philo->m_eat);
		usleep(100);
	}
	return ((void *)0);
}

void	*p_exec_routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo->time_meal = p_tool_time();
	philo->time_limit = philo->time_meal + (long long)philo->data->tt_die;
	if (pthread_create(&philo->t_id[1], NULL, p_exec_dead, param) != 0)
		return ((void *)1);
	pthread_detach(philo->t_id[1]);
	while (p_status_dead(philo->data) != 1 && p_status_option(philo->data) != 1)
	{
		p_status_fork(philo);
		p_status_eat(philo);
		p_status_sleep_think(philo);
	}
	return ((void *)0);
}

int	p_exec_start(t_data *data)
{
	int		idx;

	idx = -1;
	data->time_start = p_tool_time();
	while (++idx < data->amount)
	{
		if (pthread_create(&data->philo[idx].t_id[0], NULL,
				p_exec_routine, (void *)&data->philo[idx]) != 0)
			return (-1);
		usleep(100);
	}
	while (--idx >= 0)
		pthread_join(data->philo[idx].t_id[0], NULL);
	return (0);
}

int	p_exec_end(t_data *data)
{
	int		idx;

	pthread_mutex_destroy(&data->m_write);
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->m_option);
	idx = -1;
	while (++idx < data->amount)
	{
		pthread_mutex_destroy(&data->m_forks[idx]);
		pthread_mutex_destroy(&data->philo[idx].m_eat);
	}
	return (0);
}
