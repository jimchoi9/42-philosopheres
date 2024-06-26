#include "p_.h"

long long	philo_atoi(const char *str)
{
	long long	neg;
	long long	num;
	int			cnt;

	cnt = 0;
	num = 0;
	neg = 1;
	while (*str == '\n' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		cnt++;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (cnt > 1)
		num = 0;
	return (num * neg);
}
double	get_current_time()
{
	double now;
	struct timeval time;

	gettimeofday(&time, NULL);
	 now = (time.tv_sec * 1000 +  time.tv_usec / 1000);
	return (now );
}

int	check_dead_philo(t_data *data)
{
	int i;
	int num;

	i=0;
	num = data->num;
	// pthread_mutex_lock(&data->dead_mutex);
	while (i < data->num)
	{
		printf("checking [%d]\n", i);
		if (get_current_time() - data->philos[i].last_eat_time - data->start_time  > data->time_to_die)
		{
			data->alive = 0;
			pthread_mutex_unlock(&data->dead_mutex);
			printf("checking dead\n");
			return (1);
		}
		i++;
	}
	// pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

void	ft_usleep(int ms, t_ph *philo)
{
	double	start;

	start = get_current_time();
	// printf("%.3f\n", start);
	// printf("%.3f\n", get_current_time() - start);

	while ((get_current_time() - start) < ms)
	{
		// printf("%.3f\n", (double)get_current_time() - start);
		pthread_mutex_lock(philo->dead_mutex);
		if (philo->alive == 0)
		{
			pthread_mutex_unlock(philo->dead_mutex);
			return ;
		}
		pthread_mutex_unlock(philo->dead_mutex);
		usleep(200);
	}
	return ;
}

void ph_eat(t_ph *philo)
{
	// printf("%d is eat ready\n", philo->id);
	pthread_mutex_lock(philo->dead_mutex);
	philo->last_eat_time = get_current_time();
	pthread_mutex_unlock(philo->dead_mutex);

	pthread_mutex_lock(philo->l_mutex);
	pthread_mutex_lock(philo->r_mutex);
	// printf("%.0f fork left %d and right %d\n", get_current_time() - philo->start_time,  *philo->l_fork, *philo->r_fork);

	if (*philo->l_fork == -1 && *philo->r_fork == -1)
	{
		//먹기
		*philo->l_fork = philo->id;
		*philo->r_fork = philo->id;
		pthread_mutex_lock(philo->write_mutex);
		printf("%.0f %d has taken fork\n", get_current_time() - philo->start_time, philo->id);
		printf("%.0f %d has taken fork\n", get_current_time() - philo->start_time, philo->id);
		// pthread_mutex_lock(philo->dead_mutex);
		// printf("%.3f %d has taken fork left %d and right %d\n", get_current_time() - philo->start_time, philo->id, philo->l_fork, philo->r_fork);
		printf("%.0f %d is eating\n", get_current_time() - philo->start_time, philo->id);
		*philo->l_fork = -1;
		*philo->r_fork = -1;
		// pthread_mutex_unlock(philo->dead_mutex);
		pthread_mutex_unlock(philo->write_mutex);
		ft_usleep(philo->time_to_eat, philo);
		if (philo->must_eat > 0)
		philo->must_eat --;
	}
	// else
	// {
        pthread_mutex_unlock(philo->r_mutex);
        pthread_mutex_unlock(philo->l_mutex);
	// }
}

void ph_sleep(t_ph *philo)
{
	pthread_mutex_lock(philo->write_mutex);
	// pthread_mutex_lock(philo->dead_mutex);
	printf("%.0f %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
	// pthread_mutex_unlock(philo->dead_mutex);
	pthread_mutex_unlock(philo->write_mutex);
	ft_usleep(philo->time_to_sleep, philo);
}

void ph_think(t_ph *philo)
{
	pthread_mutex_lock(philo->write_mutex);
	// pthread_mutex_lock(philo->dead_mutex);
	if (*philo->alive)
		printf("%.0f %d is thinking\n", get_current_time() - philo->start_time, philo->id);
	// pthread_mutex_lock(philo->dead_mutex);
	pthread_mutex_unlock(philo->write_mutex);
}