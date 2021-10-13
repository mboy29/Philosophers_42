/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:31:34 by mboy              #+#    #+#             */
/*   Updated: 2021/10/08 10:31:36 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

int	p_init_philo(t_data *data)
{
	int		idx;

	data->philo = malloc(sizeof(t_philo) * data->amount);
	if (!data->philo)
		return (-1);
	idx = -1;
	while (++idx < data->amount)
	{
		data->philo[idx].idx = idx + 1;
		data->philo[idx].option = 0;
		data->philo[idx].t_id[0] = 0;
		data->philo[idx].t_id[1] = 0;
		data->philo[idx].forks[0] = idx;
		data->philo[idx].forks[1] = (idx + 1) % data->amount;
		data->philo[idx].time_meal = 0.0;
		data->philo[idx].time_limit = 0.0;
		data->philo[idx].data = data;
		pthread_mutex_init(&data->philo[idx].m_eat, NULL);
	}
	return (0);
}

int	p_init_mutex(t_data *data)
{
	int		idx;

	idx = -1;
	pthread_mutex_init(&data->m_write, NULL);
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_option, NULL);
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->amount);
	if (!data->m_forks)
		return (-1);
	while (++idx < data->amount)
		pthread_mutex_init(&data->m_forks[idx], NULL);
	return (0);
}

int	p_init_check(t_data *data)
{
	if (data->amount < 2 || data->amount > 200)
	{
		p_print_str("[ERROR]: Invalid amount of philosophers.\n");
		return (-1);
	}
	else if (data->tt_die < 60 || data->tt_eat < 60
		|| data->tt_sleep < 60 || data->tt_option < 0)
	{
		p_print_str("[ERROR]: Invalid time to.\n");
		return (-1);
	}
	return (0);
}

t_data	*p_init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->dead = 0;
	data->option = 0;
	data->time_start = 0.0;
	data->amount = p_tool_atoi(av[1]);
	data->tt_die = p_tool_atoi(av[2]);
	data->tt_eat = p_tool_atoi(av[3]);
	data->tt_sleep = p_tool_atoi(av[4]);
	data->tt_option = 0;
	if (ac == 6)
		data->tt_option = p_tool_atoi(av[5]);
	if (p_init_check(data) == -1 || p_init_philo(data) == -1
		|| p_init_mutex(data) == -1)
		return (NULL);
	return (data);
}
