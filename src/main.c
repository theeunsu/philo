/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:49:17 by eahn              #+#    #+#             */
/*   Updated: 2024/07/21 21:37:55 by eahn             ###   ########.fr       */
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
	if (init_infooo(&info) == -1)
		return (EXIT_FAILURE);
	if (start_simulation(&info) == -1)
		return (EXIT_FAILURE);
	clean_up(&info);
	return (EXIT_SUCCESS);
	// else
	// {
	// 	check_input(&info, av);  // parse_input
	// 	init_info(&info);        // data_init
	// 	start_simulation(&info); // dinner_start
	// 	clean_up(&info);         //
	// }
}
// int	main(int ac, char **av)
// {
// 	t_info	info;

// 	if (ac < 5 || ac > 6)
// 	{
// 		printf("%s\n", "Invalid arguments.");
// 		return (1);
// 	}
// 	if (init_info(&info, ac, av) == -1)
// 		return (1);
// 	if (init_philo(&info) == -1)
// 		return (1);
// 	if (init_threads(&info) == -1)
// 		return (1);
// 	return (0);
// }
