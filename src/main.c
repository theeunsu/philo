/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:49:17 by eahn              #+#    #+#             */
/*   Updated: 2024/07/07 23:15:36 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
	{
		printf("%s\n", "Invalid arguments.");
		return (1);
	}
	if (init_info(&info, ac, av) == -1)
		return (1);
	if (init_philo(&info) == -1)
		return (1);
	if (init_threads(&info) == -1)
		return (1);
	return (0);
}
