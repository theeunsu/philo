/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:49:17 by eahn              #+#    #+#             */
/*   Updated: 2024/07/29 00:03:27 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac < 5 || ac > 6)
	{
		printf("%s\n", "Invalid arguments.");
		return (EXIT_FAILURE);
	}
	if (init_info(&info, ac, av) == -1)
		return (EXIT_FAILURE);
	if (start_simulation(&info) == -1)
		return (EXIT_FAILURE);
	clean(&info);
	return (EXIT_SUCCESS);
}
