/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:00:17 by eahn              #+#    #+#             */
/*   Updated: 2024/07/28 23:02:55 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Wrapper for mutex operations

// ** MUTEX **
// Embed controls on return status
static void	mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK
			|| opcode == DESTROY))
		print_error("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		print_error("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		print_error("A deadlock would occur.");
	else if (status == EPERM)
		print_error("The current thread does not hold a lock on mutex.");
	else if (status == EBUSY)
		print_error("Mutex is locked.");
	else if (status == ENOMEM)
		print_error("The process cannot allocate enough memory.");
}

// ** MUTEX SAFE ***
// init destroy lock unlock
void	safe_mutex_operation(pthread_mutex_t *mutex, t_opcode opcode)
{
	int	status;

	status = 0;
	if (LOCK == opcode)
		mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
	{
		print_error("Error with the mutex opcode");
		return ;
	}
	if (status != 0)
	{
		mutex_error(status, opcode);
		return ;
	}
}
