/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aloc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:34:53 by mgavornik         #+#    #+#             */
/*   Updated: 2025/06/19 16:39:04 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*malloc_struct_preps(t_prepars **prepars)
{
	*prepars = (t_prepars *)malloc(sizeof(t_prepars));
	if (!*prepars)
		error_handler("Failed to allocate memory for prepars", -1, *prepars);
	return (*prepars);
}

void	*malloc_pandf(t_prepars **prepars, t_philo **philo, t_forks **forks)
{
	if (!*prepars)
		error_handler("No prepars struct", -1, *prepars);
	*forks = (t_forks *)malloc(sizeof(t_forks) * (**prepars).num_pf);
	if (!*forks)
		error_handler("Failed to allocate memory for forks", -1, *prepars);
	*philo = (t_philo *)malloc(sizeof(t_philo) * (**prepars).num_pf);
	if (!*philo)
	{
		error_handler("Failed to allocate memory for philo", -1, *prepars);
	}
	init_pandf(*prepars, *philo, *forks);
	return (*prepars);
}
