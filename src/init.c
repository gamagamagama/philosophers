/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:30:28 by mgavornik         #+#    #+#             */
/*   Updated: 2025/05/19 15:08:12 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_pandf(t_prepars *prepars, t_philo *philo, t_forks *forks)
{
	long	i;
	long	num_pf;

	num_pf = prepars->num_pf;
	i = 0;
	link_to_prepars(&prepars, &philo, &forks);
	while (i < num_pf)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		memset(&forks[i], 0, sizeof(t_forks));
		mutex_codes((&(forks[i].fork)), INIT);
		prepars->forks[i].fork_id = i;
		philo->fil_id = (i);
		philo->preps = prepars;
		link_forks(philo, forks, i);
		i++;
	}
}

void	init_prep(t_prepars *prepars)
{
	memset(prepars, 0, sizeof(t_prepars));
	prepars->time_d = malloc(sizeof(t_time_data));
	prepars->start_simul = 0;
	if (!prepars->time_d)
	{
		error_handler("Failed to allocate memory for prepars fields", -1,
			prepars);
	}
	mutex_codes(&prepars->prep_mutex, INIT);
	mutex_codes(&prepars->print_mutex, INIT);
}

void	set_thrds_ready(void *arg)
{
	t_prepars	*prepars;

	prepars = (t_prepars *)arg;
	prepars->threads_ready = 1;
}