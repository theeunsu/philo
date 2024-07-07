/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_thread_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:02:09 by eahn              #+#    #+#             */
/*   Updated: 2024/07/02 22:45:43 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Wrapper for mutex and thread operations

// ** MUTEX **
// Embed controls on return status
static void	handle_mutex_error(int status, t_opcode opcode)
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
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		print_error("Error with the mutex opcode");
}

// ** THREADS **
static void	handle_thread_error(int status, t_opcode opcode)
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
void	safe_thread_operation(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		print_error("Use (CREATE | JOIN | DETACH)");
}
