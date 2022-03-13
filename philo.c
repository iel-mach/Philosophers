/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 05:58:12 by iel-mach          #+#    #+#             */
/*   Updated: 2022/03/13 01:31:22 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	supervisor(t_args args, t_philo *philos)
{
	int			finish_eat;
	int			i;

	i = -1;
	finish_eat = 0;
	while (finish_eat != args.n_philo)
	{
		finish_eat = 0;
		i = -1;
		while (++i < args.n_philo)
		{
			if (philos[i].nb_eat == args.t_must_eat)
				finish_eat++;
			if (get_time() - philos[i].last_time_eat >= args.t_die * 1000)
			{
				pthread_mutex_lock(philos[i].m_died);
				printf("[%lld] [%d] Died\n", \
					(get_time() - philos ->args->start_time) \
					/ 1000, philos[i].id + 1);
				exit (0);
			}
		}
	}
}

int	init_args(t_args *args, int argc, char **argv)
{
	check_argc(argc);
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->t_must_eat = -1;
	if (argc == 6)
		args->t_must_eat = ft_atoi(argv[5]);
	if ((args->t_must_eat <= 0 && argc == 6) || args->n_philo <= 0
		|| args->t_die < 0 || args -> t_eat < 0
		|| args->t_sleep < 0)
	{
		write(2, "Invalid argument!\n", 18);
		return (1);
	}
	while (argc > 1)
	{
		if (!check_digit(argv[argc - 1]))
		{
			write(2, "Invalid argumentt!\n", 19);
			return (1);
		}
		argc--;
	}
	return (0);
}

void	creat_philos(t_args args, pthread_mutex_t *mutex, int i)
{
	long long		t;
	t_philo			*philos;
	pthread_mutex_t	*m_died;

	m_died = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(m_died, NULL);
	philos = malloc(sizeof(t_philo) * args.n_philo);
	philos->thread = malloc(sizeof(pthread_t) * args.n_philo);
	t = get_time();
	while (++i < args.n_philo)
	{
		philos[i].id = i;
		philos[i].args = &args;
		philos[i].mutex = mutex;
		philos[i].nb_eat = 0;
		philos[i].m_died = m_died;
		philos[i].last_time_eat = get_time();
		philos[i].is_eating = 0;
		philos[i].args->start_time = t;
		if (pthread_create(philos->thread + i, NULL, &routine, &philos[i]) != 0)
			write (2, "faild creat thread\n", 19);
		usleep(100);
	}
	supervisor(args, philos);
}

pthread_mutex_t	*creat_forks(t_args args)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * args.n_philo);
	while (i < args.n_philo)
	{
		pthread_mutex_init(mutex + i, NULL);
		i++;
	}
	return (mutex);
}

int	main(int ac, char **av)
{
	t_args			args;
	pthread_mutex_t	*mutex;
	int				i;

	i = -1;
	if (init_args(&args, ac, av))
		return (1);
	mutex = creat_forks(args);
	creat_philos(args, mutex, i);
}
