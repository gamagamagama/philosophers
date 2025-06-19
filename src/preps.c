/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:59:26 by mgavorni          #+#    #+#             */
/*   Updated: 2025/06/19 16:14:01 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *str)
{
	if (!str || !*str)
		return (error_handler("is num failed", -1, NULL));
	return (*str >= '0' && *str <= '9');
}

int	is_deli(char *str)
{
	if (!str || !*str)
		return (error_handler("is deli failed", -1, NULL));
	return (*str == ' ' || (*str >= 9 && *str <= 13));
}

long	kindtoi(char **str, t_prepars *prepars)
{
	int		i;
	long	res;
	char	*s;

	s = *str;
	i = 0;
	res = 0;
	while (is_deli(&s[i]))
		i++;
	if (s[i] == '-' || !is_num(&s[i]))
		return (error_handler("input is not num or is minus", -1, prepars));
	while (s[i] && s[i] == '+')
	{
		i++;
	}
	while (s[i] && is_num(&s[i]))
	{
		res = res * 10 + (s[i] - '0');
		if (res > INT_MAX)
			return (error_handler("input is out of INT_MAX range", -1,
					prepars));
		i++;
	}
	return (res);
}

void	*prepare_it(t_prepars **prepars, char **str)
{
	int	i;

	i = 1;
	init_prep(*prepars);
	if (str[i])
	{
		(*prepars)->num_pf = kindtoi(&str[i], *prepars);
		(*prepars)->ttd = kindtoi(&str[++i], *prepars);
		(*prepars)->tte = kindtoi(&str[++i], *prepars);
		(*prepars)->tts = kindtoi(&str[++i], *prepars);
	}
	if (str[++i])
		(*prepars)->times_to = kindtoi(&str[i], *prepars);
	else
		(*prepars)->times_to = -1;
	return (prepars);
}
