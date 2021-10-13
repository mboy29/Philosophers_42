/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:31:43 by mboy              #+#    #+#             */
/*   Updated: 2021/10/08 10:31:44 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

int	p_status_dead(t_data *data)
{
	pthread_mutex_lock(&data->m_dead);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->m_dead);
	return (0);
}

void	p_status_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_forks[philo->forks[0]]);
	p_tool_status(philo, FORK);
	pthread_mutex_lock(&philo->data->m_forks[philo->forks[1]]);
	return (p_tool_status(philo, FORK));
}

void	p_status_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_eat);
	if (philo->data->tt_option == 0 || (philo->option < philo->data->tt_option
			&& philo->option < philo->data->tt_option))
	{
		if (philo->data->tt_option > 0)
		{
			pthread_mutex_lock(&philo->data->m_option);
			philo->option += 1;
			if (philo->option == philo->data->tt_option)
				philo->data->option += 1;
			pthread_mutex_unlock(&philo->data->m_option);
		}
		philo->time_meal = p_tool_time();
		philo->time_limit = philo->time_meal + (long long)philo->data->tt_die;
		p_tool_status(philo, EAT);
		usleep(philo->data->tt_eat * 1000);
		pthread_mutex_unlock(&philo->data->m_forks[philo->forks[0]]);
		pthread_mutex_unlock(&philo->data->m_forks[philo->forks[1]]);
	}
	return ((void)pthread_mutex_unlock(&philo->m_eat));
}

void	p_status_sleep_think(t_philo *philo)
{
	p_tool_status(philo, SLEEP);
	usleep(philo->data->tt_sleep * 1000);
	return (p_tool_status(philo, THINK));
}

int	p_status_option(t_data *data)
{
	pthread_mutex_lock(&data->m_option);
	if (data->tt_option > 0 && data->option == data->amount)
	{
		p_tool_status(&data->philo[0], OPTION);
		pthread_mutex_unlock(&data->m_option);
		return (1);
	}
	pthread_mutex_unlock(&data->m_option);
	return (0);
}
