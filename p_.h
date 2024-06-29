/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:43:57 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/27 18:21:00 by jimchoi          ###   ########.fr       */
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
    int l_fork;
    int r_fork;
	double last_eat_time;
	int dead;
	
	pthread_mutex_t l_mutex;
	pthread_mutex_t r_mutex;

	// struct timeval time;
	pthread_t thread;

	t_data *data;

}t_ph;

typedef struct s_data
{
	int num;
	int is_dead;
	int life_time;
	int eat_time;
	int sleep_time;
	int *forks;
	// double last_eat_time;
	double start_time;
	t_ph *philo;


	pthread_mutex_t start_mutex;
	pthread_mutex_t dead_mutex;
	pthread_mutex_t write_mutex;

}t_data;