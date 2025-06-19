/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:01:09 by mgavornik         #+#    #+#             */
/*   Updated: 2025/05/19 16:10:01 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	link_all_philos(t_prepars **prepars, t_philo **philo, t_forks **forks)
{
	long	i;
	long	num_pf;

	i = 0;
	if (!*prepars || !*philo || !*forks)
		error_handler("link_all_philos: Invalid input", -1, *prepars);
	num_pf = (**prepars).num_pf;
	while (i < num_pf)
	{
		(*philo)[i].fil_id = i;
		(*philo)[i].preps = *prepars;
		(*philo)[i].right = &(*forks)[i];
		(*philo)[i].left = &(*forks)[(i + 1) % num_pf];
		i++;
	}
}

void	link_to_prepars(t_prepars **prepars, t_philo **philo, t_forks **forks)
{
	if (!*prepars || !*philo || !*forks)
		error_handler("something in link prepas goes wrong", -1, *prepars);
	(**prepars).philos = *philo;
	(**prepars).forks = *forks;
	(**philo).preps = *prepars;
}

void	link_forks(t_philo *philo, t_forks *forks, long pos)
{
	philo->right = &forks[pos];
	philo->left = &forks[(pos + 1) % philo->preps->num_pf];
	if (philo->fil_id % 2 == 0)
	{
		philo->right = &forks[pos];
		philo->left = &forks[(pos + 1) % philo->preps->num_pf];
	}
}