/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:02:09 by eahn              #+#    #+#             */
/*   Updated: 2024/07/21 22:04:36 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Wrapper for thread operations

static void	thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		print_error("No resources to create another thread");
	else if (status == EPERM)
		print_error("The caller does not have appropriate permission .");
	else if (status == EINVAL && opcode == CREATE)
		print_error("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		print_error("The thread is not a joinable thread.");
	else if (status == ESRCH)
		print_error("No thread could be found.");
	else if (status == EDEADLK)
		print_error("A deadlock was detected.");
}

// One function to handle all thread errors
// create join detach
void	thread_operation(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		thread_error(pthread_detach(*thread), opcode);
	else
		print_error("Use (CREATE | JOIN | DETACH)");
}
