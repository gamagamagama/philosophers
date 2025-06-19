/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:18:46 by mgavorni          #+#    #+#             */
/*   Updated: 2025/06/19 14:22:00 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_w(t_philo *philo)
{
	if (philo->fil_id % 2 == 0 && !flag_end_simul(philo->preps))
	{
		mutex_codes(&philo->right->fork, LOCK);
		mutex_codes(&philo->left->fork, LOCK);
	}
	else if (!flag_end_simul(philo->preps))
	{
		mutex_codes(&philo->left->fork, LOCK);
		mutex_codes(&philo->right->fork, LOCK);
	}
}

void	drop_forks_w(t_philo *philo)
{
	mutex_codes(&philo->left->fork, UNLOCK);
	mutex_codes(&philo->right->fork, UNLOCK);
}

void	sleep_w(t_philo *philo)
{
	philo->status = SLEEPING;
	do_mutex(&philo->preps->print_mutex, do_print, philo);
	my_usleep(philo->preps->tts, philo->preps->time_d,
		&philo->preps->dead_flag);
}

void	thinking_w(t_philo *philo)
{
	philo->status = THINKING;
	do_mutex(&philo->preps->print_mutex, do_print, philo);
}
