/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:31:48 by mboy              #+#    #+#             */
/*   Updated: 2021/10/08 10:31:50 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

long long	p_tool_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	p_tool_atoi(char *str)
{
	int		idx;
	int		nbr;

	nbr = 0;
	idx = -1;
	while (str[++idx])
	{
		if (str[idx] < 48 || str[idx] > 57)
			return (-1);
		nbr = nbr * 10 + (str[idx] - 48);
	}
	return (nbr);
}

int	p_tool_strcmp(const char *s1, const char *s2)
{
	int	idx;

	idx = 0;
	while (s2[idx] && s1[idx] && s1[idx] == s2[idx])
		idx++;
	return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
}

void	p_tool_status(t_philo *philo, char *mess)
{
	static int	dead = 0;
	static int	option = 0;

	pthread_mutex_lock(&philo->data->m_write);
	if (dead == 0 && option == 0)
	{
		if (p_tool_strcmp(mess, OPTION) == 0)
		{
			option = 1;
			p_print_status(philo, mess);
			return ((void)pthread_mutex_unlock(&philo->data->m_write));
		}
		p_print_status(philo, mess);
		if (p_tool_strcmp(mess, DEAD) == 0)
			dead = 1;
	}
	return ((void)pthread_mutex_unlock(&philo->data->m_write));
}
