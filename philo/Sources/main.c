/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:31:38 by mboy              #+#    #+#             */
/*   Updated: 2021/10/08 10:31:40 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = p_init_data(ac, av);
		if (!data || p_exec_start(data) == -1)
			return (-1);
		return (p_exec_end(data));
	}
	p_print_str("[ERROR]: Wrong amount of arguments.\n");
	return (-1);
}
