/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:58:45 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 17:00:16 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>

void	print_log(t_philo *philo, char *message)
{
	suseconds_t	time;

	pthread_mutex_lock(&philo->ctx->write_lock);
	time = current_time() - philo->ctx->epoch;
	pthread_mutex_lock(&philo->ctx->dead_lock);
	if (philo->ctx->dead)
	{
		pthread_mutex_unlock(&philo->ctx->dead_lock);
		pthread_mutex_unlock(&philo->ctx->write_lock);
		return ;
	}
	if (*message == *DIED)
		philo->ctx->dead = true;
	pthread_mutex_unlock(&philo->ctx->dead_lock);
	printf("%ld%5d  %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->ctx->write_lock);
}
