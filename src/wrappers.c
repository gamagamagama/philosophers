/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:28:14 by mgavornik         #+#    #+#             */
/*   Updated: 2025/06/19 16:24:05 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	do_meal_t(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	get_now(philo->preps->time_d);
	philo->meal_time = philo->preps->time_d->my_time;
}

int	eat_sleep_end_w(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!flag_end_simul(philo->preps))
	{
		eat_sleep_w(philo);
		if (meal_limit(philo))
		{
			philo->done_meals = 1;
			return (1);
		}
	}
	return (0);
}

void	eat_sleep_w(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	take_forks_w(philo);
	eating_w(philo);
	drop_forks_w(philo);
	sleep_w(philo);
}

int	break_meal_wr(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->done_meals)
	{
		do_mutex(&philo->preps->prep_mutex, do_meal_t, philo);
		my_usleep(100, philo->preps->time_d, &philo->preps->dead_flag);
		return (1);
	}
	return (0);
}

void	eating_w(t_philo *philo)
{
	philo->status = EATING;
	do_mutex(&philo->preps->print_mutex, do_print, philo);
	do_mutex(&philo->preps->prep_mutex, do_meal_t, philo);
	my_usleep(philo->preps->tte, philo->preps->time_d,
		&philo->preps->dead_flag);
	if (get_now(philo->preps->time_d) > philo->preps->tte)
		philo->full_flag = 1;
}

// mutex_codes(&philo->preps->print_mutex, LOCK);
// print_status(EATING, philo);
// mutex_codes(&philo->preps->print_mutex, UNLOCK);
// get_now(philo->preps->time_d);
// set_long(&philo->preps->prep_mutex, &philo->meal_time,
//	get_now(philo->preps->time_d));
// printf(YEL"now : %ld\n"RESET, philo->meal_time);