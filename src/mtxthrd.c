/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtxthrd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:24:57 by mgavorni          #+#    #+#             */
/*   Updated: 2025/05/19 15:31:54 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_codes(t_mutex *mutex, t_mutx_code code)
{
	if (!mutex)
		return ;
	if (code == LOCK && mutex)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK && mutex)
		pthread_mutex_unlock(mutex);
	else if (code == INIT && mutex)
		pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY && mutex)
		pthread_mutex_destroy(mutex);
	else
		error_handler("Mutex operation fuckdup", -1, NULL);
}

void	pthread_codes(pthread_t *pthr, t_thread_code code,
		void *(*start_rout)(void *), void *arg)
{
	if (code == CREATE)
		pthread_create(pthr, NULL, start_rout, arg);
	else if (code == JOIN)
		pthread_join(*pthr, NULL);
	else if (code == DETACH)
		pthread_detach(*pthr);
	else
		error_handler("Thread operation fuckdup", -1, NULL);
}

void	wait_for_threads(t_prepars *preps)
{
	while (!flag_get_tf(&preps->prep_mutex, &preps->threads_ready))
		;

}

void	do_mutex(t_mutex *mutex, void (*op)(void *), void *arg)
{
	mutex_codes(mutex, LOCK);
	op(arg);
	mutex_codes(mutex, UNLOCK);
}
