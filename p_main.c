/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:38:13 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/27 19:30:35 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_.h"


double	get_time_stamp()
{
	double now;
	struct timeval time;


	gettimeofday(&time, NULL);
	 now = (time.tv_sec * 1000 +  time.tv_usec / 1000);
	return (now);
}

int	philo_usleep(size_t time)
{
	size_t	start;

	start = get_time_stamp();
	while ((get_time_stamp() - start) < time)
		usleep(500);
	return (0);
}

int	init_philos(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->num)
	{
		data->philo[i].id = i;
		data->philo[i].r_fork = i ;
        data->philo[i].l_fork = (i + 1) % data->num;
		data->philo[i].eat_count = 0;
		data->philo[i].last_eat_time = 0;
		data->philo[i].dead = 0;
		pthread_mutex_init(&data->philo[i].l_mutex, NULL);
		pthread_mutex_init(&data->philo[i].r_mutex, NULL);
		data->philo[i].data = data;
	}
	return (0);
}

int init_data(char **argv, int argc, t_data *data)
{
	int i;

	i=-1;
	data->num = 5;
	data->is_dead = 0;
	data->life_time = 410;
	data->eat_time = 200;
	data->sleep_time = 200;
	data->start_time = get_time_stamp();
	data->forks = malloc(sizeof(int) * data->num);
	data->philo  = malloc(sizeof(t_ph ) * data->num);
	if ( !data->philo || !data->forks)
	  {
        free(data->forks);
        return (1);
    }
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	
	while (++i < data->num)
		data->forks[i] = -1;
	// data->philo = malloc(sizeof(t_ph *) * data->num + 1);
	if (init_philos(data))
		return (1);
	return (0);
}


void *check_dead(void *arg)
{
    t_data *data = *(t_data **)arg;
	pthread_mutex_lock(&data->start_mutex);
	pthread_mutex_unlock(&data->start_mutex);

    printf("############check_dead############\n isdead = %d\n", data->is_dead);

    // pthread_mutex_lock(&data->check_dead);
    // printf("############check_dead############\n");
    while(1)
    {
	pthread_mutex_lock(&data->start_mutex);
        // pthread_mutex_lock(&data->dead_mutex);
        if (data->is_dead)
        {
            data->is_dead = 2;
            pthread_mutex_unlock(&data->dead_mutex);
            break ;

        }
        // pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_unlock(&data->start_mutex);

        // usleep(100);
    }
    // pthread_mutex_unlock(&data->check_dead);
    printf("############check_dead_end############\n");

        return ((void *)1);
}

int is_alive(t_ph *philo)
{
    pthread_mutex_lock(&philo->data->dead_mutex);
        if (philo->data->is_dead)
        {
            pthread_mutex_unlock(&philo->data->dead_mutex);
            return (0);
        }
    pthread_mutex_unlock(&philo->data->dead_mutex);
        return (1);
}
void eating(t_ph *philo)
{
		pthread_mutex_lock(&philo->data->write_mutex);
		printf("fork[%d] = %d, fork[%d] = %d\n", philo->l_fork, philo->data->forks[philo->l_fork], philo->r_fork, philo->data->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->write_mutex);
	pthread_mutex_lock(&philo->l_mutex);
	pthread_mutex_lock(&philo->r_mutex);
	
		pthread_mutex_lock(&philo->data->write_mutex);
		if (philo->data->forks[philo->l_fork] == -1)
		{
			
		printf("%d has taken a  left fork\n", philo->id);
			philo->data->forks[philo->l_fork] = philo->id;
		}
		pthread_mutex_unlock(&philo->data->write_mutex);
	
		pthread_mutex_lock(&philo->data->write_mutex);
		if (philo->data->forks[philo->r_fork] == -1)
		{
		printf("%d has taken a  right fork\n", philo->id);
		philo->data->forks[philo->r_fork] = philo->id;
			
		}
		pthread_mutex_unlock(&philo->data->write_mutex);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&philo->r_mutex);
	// 	pthread_mutex_unlock(&philo->l_mutex);
	// }
	
	if (philo->data->forks[philo->l_fork] ==  philo->id && philo->data->forks[philo->r_fork] ==  philo->id)
	{
			pthread_mutex_lock(&philo->data->write_mutex);
		printf("fork[%d] = %d, fork[%d] = %d\n", philo->l_fork, philo->data->forks[philo->l_fork], philo->r_fork, philo->data->forks[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->write_mutex);
		pthread_mutex_lock(&philo->data->write_mutex);
		printf("%.0f %d is eating\n", get_time_stamp() - philo->data->start_time , philo->id);
		philo->eat_count++;
		philo->last_eat_time = get_time_stamp();
		pthread_mutex_unlock(&philo->data->write_mutex);
		usleep(200000);

	}
		philo->data->forks[philo->l_fork] = -1;
		philo->data->forks[philo->r_fork] = -1;
		pthread_mutex_unlock(&philo->l_mutex);
		pthread_mutex_unlock(&philo->r_mutex);
	// else
	// {
	// 	pthread_mutex_unlock(&philo->l_mutex);
	// 	pthread_mutex_unlock(&philo->r_mutex);
	// }
}

void *philosopher(void *arg)
{
	t_ph *philo = (t_ph *)arg;

	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	philo->last_eat_time = get_time_stamp();
	if (philo->id % 2 == 0)
		philo_usleep(1);
	int i = 0;
	while(1)
	{
		if (philo->eat_count > 5)
			break ;
		eating(philo);
		i++;
	}
}


void	make_thread(t_data *data)
{
	pthread_t check_thread;
	int i;

	i = -1;
	pthread_mutex_lock(&data->start_mutex);
	// if (pthread_create(&check_thread, NULL, check_dead, &data))
	// {
	// 	printf("thread create error\n");
	// 	exit(1) ;
	// }
	while (++i < data->num)
	{
		if (pthread_create(&data->philo[i].thread, NULL, philosopher, &data->philo[i]))
		{
			printf("thread create error\n");
			exit(1) ;
		}
		
	}
	i = -1;
	pthread_mutex_unlock(&data->start_mutex);
	// if (pthread_join(check_thread, NULL))
	// {
	// 	printf("thread join error\n");
	// 	exit(1) ;
	// }
	while (++i < data->num)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			printf("thread join error\n");
			exit(1) ;
		}
	}
printf("############pthread_join############\n");
	
}

int main(int argc, char *argv[])
{
	t_data *data;

	if (argc != 5 && argc != 6)
        return (1);
    data = malloc(sizeof(t_data));
    memset(data, 0, sizeof(t_data));


	if (init_data(argv, argc, data))
		return (1);
	make_thread(data);

}