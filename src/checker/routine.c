/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:53:07 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 17:00:16 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>

static _Bool	dead(t_philo *philo)
{
	_Bool	status;

	status = false;
	pthread_mutex_lock(&philo->ctx->dead_lock);
	if (philo->ctx->dead)
		status = true;
	pthread_mutex_unlock(&philo->ctx->dead_lock);
	return (status);
}

static _Bool	starve(t_philo *philo)
{
	_Bool	status;

	status = false;
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->ctx->meals == philo->meals)
		status = true;
	pthread_mutex_unlock(&philo->meal_lock);
	return (status);
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *) philo;
	eating(p);
	sleeping(p);
	thinking(p);
	if (starve(p) || dead(p))
		return (philo);
	return (routine(philo));
}
