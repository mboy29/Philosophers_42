/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:39:03 by mboy              #+#    #+#             */
/*   Updated: 2021/10/12 18:39:04 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

void	p_print_str(char *str)
{
	int		idx;

	idx = -1;
	while (str[++idx])
		write(1, &str[idx], 1);
	return ;
}

void	p_print_nbr(long long nbr)
{
	char	c;

	if (nbr < 10)
	{
		c = (nbr % 10) + 48;
		write(1, &c, 1);
	}
	else
	{
		p_print_nbr(nbr / 10);
		c = (nbr % 10) + 48;
		write(1, &c, 1);
	}
	return ;
}

void	p_print_status(t_philo *philo, char *mess)
{
	p_print_nbr((long long)(p_tool_time() - philo->data->time_start));
	write(1, "\t", 1);
	if (p_tool_strcmp(mess, OPTION) != 0)
	{
		p_print_nbr(philo->idx);
		write(1, " ", 1);
	}
	p_print_str(mess);
	write(1, "\n", 1);
	return ;
}
