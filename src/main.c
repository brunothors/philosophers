/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:56:32 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 17:00:16 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static int	input_error(int argc)
{
	if (argc < 2)
		ft_putendl_fd("philo: ...\n", STDERR_FILENO);
	else if (argc < 3)
		ft_putendl_fd(
			"philo: Only my soul should by immortal!\n", STDERR_FILENO);
	else if (argc < 4)
		ft_putendl_fd("philo: Should I starve?\n", STDERR_FILENO);
	else if (argc < 5)
		ft_putendl_fd("philo: No one survives without sleep!\n", STDERR_FILENO);
	else if (argc > 6)
		ft_putendl_fd("philo: What is this supposed to be?\n", STDERR_FILENO);
	else
		return (false);
	ft_putendl_fd(
		"./philo 200 200 200 200 200\n"
		"        |   |   |   |   |\n"
		"        |   |   |   |   Number of meals\n"
		"        |   |   |   Time to sleep\n"
		"        |   |   Time to eat\n"
		"        |   Time to die\n"
		"        Number of philosophers\n", STDERR_FILENO);
	return (true);
}

static int	parse_inputs(t_ctx *ctx, char **argv)
{
	ctx->philos = ft_atol(argv[1]);
	if (ctx->philos < 1 || ctx->philos > PHILOSOPHERS)
		return (false);
	ctx->die = ft_atol(argv[2]);
	if (ctx->die < 60)
		return (false);
	ctx->eat = ft_atol(argv[3]);
	if (ctx->eat < 60)
		return (false);
	ctx->sleep = ft_atol(argv[4]);
	if (ctx->sleep < 60)
		return (false);
	if (argv[5])
	{
		ctx->meals = ft_atol(argv[5]);
		if (ctx->meals < 0)
			return (false);
	}
	else
		ctx->meals = -1;
	return (true);
}

static void	create_threads(t_philo *philos)
{
	int	i;

	pthread_create(&philos->ctx->supervisor, NULL, monitoring, philos);
	i = 0;
	while (i < philos->ctx->philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i += 2;
	}
	usleep(250);
	i = 1;
	while (i < philos->ctx->philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i += 2;
	}
	pthread_join(philos->ctx->supervisor, NULL);
	i = 0;
	while (i < philos->ctx->philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_ctx	ctx;
	t_philo	philo[PHILOSOPHERS];
	t_mtx	fork[PHILOSOPHERS];

	ctx = (t_ctx){0};
	if (input_error(argc))
		return (EXIT_FAILURE);
	if (!parse_inputs(&ctx, argv))
	{
		ft_putendl_fd("Bad format input!\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	init_philos(&ctx, philo, fork);
	create_threads(philo);
	destroy_all(&ctx, philo);
	return (EXIT_SUCCESS);
}
