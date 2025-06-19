/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:13:35 by mgavorni          #+#    #+#             */
/*   Updated: 2025/06/19 16:23:08 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_now(philo->preps->time_d);

	if ((status == LEFT_FORK) && !flag_end_simul(philo->preps))
	{
		elapsed = get_now(philo->preps->time_d);
	}
	else if ((status == RIGHT_FORK) && !flag_end_simul(philo->preps))
	{
		elapsed = get_now(philo->preps->time_d);
	}
	else if (status == EATING && !flag_end_simul(philo->preps))
	{
		printf(BLUE "%ld %ld is eating\n" RESET, elapsed, philo->fil_id + 1);
	}
	else if (status == THINKING && !flag_end_simul(philo->preps))
	{
		printf(GREEN "%ld %ld is thinking\n" RESET, elapsed, philo->fil_id + 1);
	}
	else if (status == SLEEPING && !flag_end_simul(philo->preps))
	{
		printf(YEL "%ld %ld is sleeping\n" RESET, elapsed, philo->fil_id + 1);
	}
	elapsed = get_now(philo->preps->time_d);
}

void	do_print(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_status(philo->status, philo);
}
