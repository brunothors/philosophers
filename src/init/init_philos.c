/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:54:00 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 17:00:16 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>

void	init_philos(t_ctx *ctx, t_philo *philos, t_mtx *forks)
{
	int	i;

	pthread_mutex_init(&ctx->write_lock, NULL);
	pthread_mutex_init(&ctx->dead_lock, NULL);
	ctx->dead = false;
	i = 0;
	while (i < ctx->philos)
	{
		philos[i].id = i + 1;
		philos[i].meals = 0;
		philos[i].dead = false;
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		philos[i].r_fork = &forks[i];
		pthread_mutex_init(philos[i].r_fork, NULL);
		if (i == ctx->philos - 1)
			philos[i].l_fork = &forks[0];
		else
			philos[i].l_fork = &forks[i + 1];
		philos[i].ctx = ctx;
		ctx->epoch = current_time();
		philos[i].last_meal = ctx->epoch;
		i++;
	}
}
