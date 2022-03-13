/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:32:25 by iel-mach          #+#    #+#             */
/*   Updated: 2022/03/10 16:49:01 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_philo *i)
{
	pthread_mutex_lock(i->m_died);
	printf("[%lld] [%d] is eating\n", \
		(get_time() - i ->args->start_time) / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
	ft_usleep(i->args->t_eat * 1000);
}

void	p_sleep(t_philo *i)
{
	pthread_mutex_lock(i->m_died);
	printf("[%lld] [%d] is sleeping\n", \
		(get_time() - i ->args->start_time) / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
	ft_usleep(i->args->t_eat * 1000);
}

void	p_think(t_philo *i)
{
	pthread_mutex_lock(i->m_died);
	printf("[%lld] [%d] is thinking\n", \
		(get_time() - i ->args->start_time) / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
}

void	p_takefork(t_philo *i)
{
	pthread_mutex_lock(i->m_died);
	printf("[%lld] [%d] has taken a fork\n", \
		(get_time() - i ->args->start_time) / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
}

void	*routine(void *philos)
{
	t_philo		*ph;
	long long	t;

	ph = (t_philo *)philos;
	t = get_time ();
	while (1)
	{
		pthread_mutex_lock(&ph->mutex[ph->id]);
		p_takefork(ph);
		pthread_mutex_lock(&ph->mutex[(ph->id + 1) % ph->args->n_philo]);
		ph->last_time_eat = get_time();
		p_takefork(ph);
		p_eat(ph);
		pthread_mutex_unlock(&ph->mutex[ph->id]);
		pthread_mutex_unlock(&ph->mutex[(ph->id + 1) % ph->args->n_philo]);
		if (ph->args->t_must_eat != -1)
			ph->nb_eat++;
		if (ph->args->t_must_eat == ph->nb_eat)
			break ;
		p_sleep(ph);
		p_think(ph);
	}
	return (0);
}
