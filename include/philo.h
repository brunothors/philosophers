/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnespoli <bnespoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:51:38 by bnespoli          #+#    #+#             */
/*   Updated: 2025/01/21 16:52:05 by bnespoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>

# define PHILOSOPHERS 200

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define RFORK "has taken a fork"
# define LFORK "has taken a fork"
# define DIED "\033[0;91mdied\033[0m"

typedef struct s_ctx	t_ctx;
typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mtx;

struct s_philo
{
	pthread_t	thread;
	short		id;
	suseconds_t	last_meal;
	int			meals;
	t_mtx		meal_lock;
	_Bool		dead;
	t_mtx		*r_fork;
	t_mtx		*l_fork;
	t_ctx		*ctx;
};

struct	s_ctx
{
	pthread_t	supervisor;
	_Bool		dead;
	suseconds_t	die;
	suseconds_t	eat;
	suseconds_t	sleep;
	suseconds_t	epoch;
	int			philos;
	int			meals;
	t_mtx		dead_lock;
	t_mtx		write_lock;
};

long		ft_atol(char *pntr);
void		ft_putendl_fd(char *str, int fd);
void		ft_usleep(suseconds_t milliseconds);
suseconds_t	current_time(void);
void		print_log(t_philo *philo, char *message);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		*monitoring(void *philos);
void		*routine(void *philos);
void		init_philos(t_ctx *ctx, t_philo *philos, t_mtx *forks);
void		destroy_all(t_ctx *ctx, t_philo *philos);

#endif
