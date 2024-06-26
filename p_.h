/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:43:57 by jimchoi           #+#    #+#             */
/*   Updated: 2024/07/01 21:35:39 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <memory.h>

typedef struct s_data t_data;


typedef struct s_ph
{
    int id;
    int eat_count;
    int must_eat;
    int *l_fork;
    int *r_fork;
	double start_time;
	double last_eat_time;
	int *alive;
    int time_to_die;
	int time_to_eat;
	int time_to_sleep;

	// int *forks;
	// pthread_mutex_t *fork_mutex;
	pthread_mutex_t *l_mutex;
	pthread_mutex_t *r_mutex;
	
	pthread_mutex_t *start_mutex;
	pthread_mutex_t *dead_mutex;
	pthread_mutex_t *write_mutex;
	pthread_t thread;

}t_ph;

typedef struct s_data
{
	int num;
	int alive;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;
	double start_time;

	int *forks;
	pthread_mutex_t *fork_mutex;

	t_ph *philos;

	pthread_mutex_t start_mutex;
	pthread_mutex_t dead_mutex;
	pthread_mutex_t write_mutex;

}t_data;

long long	philo_atoi(const char *str);
double	get_current_time();
int	check_dead_philo(t_data *data);
void	ft_usleep(int ms, t_ph *philo);
void ph_eat(t_ph *philo);
void ph_sleep(t_ph *philo);
void ph_think(t_ph *philo);
