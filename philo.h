/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 06:24:02 by iel-mach          #+#    #+#             */
/*   Updated: 2022/03/10 16:36:17 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_args{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			t_must_eat;
	long long	start_time;

}	t_args;

typedef struct s_philo
{
	long long		last_time_eat;
	int				id;
	int				nb_eat;
	int				is_eating;
	t_args			*args;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*m_died;
	pthread_t		*thread;

}	t_philo;

int			ft_atoi(char *s);
int			ft_int_args(t_args *args, char **s, int ac);
int			check_digit(char *s);
long long	get_time(void);
void		ft_usleep(useconds_t usec);
int			init_args(t_args *args, int argc, char **argv);
void		*routine(void *philos);
void		p_takefork(t_philo *i);
void		p_think(t_philo *i);
void		p_sleep(t_philo *i);
void		p_eat(t_philo *i);
int			check_digit(char *s);
void		check_argc(int argc);
void		creat_philos(t_args args, pthread_mutex_t *mutex, int i);
void		supervisor(t_args args, t_philo *philos);
#endif