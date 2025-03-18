/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:54:44 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 17:00:16 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

static void	right(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, RFORK);
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, LFORK);
}

static void	left(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, LFORK);
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, RFORK);
}

void	eating(t_philo *philo)
{
	if (philo->ctx->philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_log(philo, RFORK);
		ft_usleep(philo->ctx->die + 11);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	if (philo->id % 2 == 0)
		right(philo);
	else
		left(philo);
	print_log(philo, EAT);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = current_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->ctx->eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
