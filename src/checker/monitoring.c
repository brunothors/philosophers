/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:52:43 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 16:52:56 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

static _Bool	check_dead(t_philo *philo, int *meals)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (current_time() - philo->last_meal > philo->ctx->die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		print_log(philo, DIED);
		return (true);
	}
	else
		*meals += philo->meals;
	pthread_mutex_unlock(&philo->meal_lock);
	return (false);
}

void	*monitoring(void *philos)
{
	t_philo	*p;
	int		i;
	int		meals;

	p = (t_philo *) philos;
	i = 0;
	meals = 0;
	while (i < p->ctx->philos)
		if (check_dead(&p[i++], &meals))
			return (philos);
	if (meals == p->ctx->philos * p->ctx->meals)
		return (philos);
	return (monitoring(philos));
}
