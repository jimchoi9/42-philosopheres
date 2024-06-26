#include "philo.h"

double	get_time_stamp(t_data *data)
{
	double now;

	gettimeofday(&(data->time), NULL);
	 now = (data->time.tv_sec * 1000 +  data->time.tv_usec / 1000);
	// printf("start_time : %.0f\n", data->start_time);	
	// printf("now_time : %.0f\n", now);	
	// printf("%.0f ", now - data->start_time);	
	return (now - data->start_time);
}

void	philo_eating(t_ph *philo)
{		
	// if (philo->data->fork[philo->left])
		{
			pthread_mutex_lock(&philo->data->fork_mutex[philo->left]);
			philo->data->fork[philo->left] = philo->id;
		}
		// if (philo->data->fork[philo->right])
		{
			pthread_mutex_lock(&philo->data->fork_mutex[philo->right]);
			philo->data->fork[philo->right] =  philo->id;
		}


		// DKJHFS
		if (philo->data->fork[philo->left] ==  philo->id && philo->data->fork[philo->right] ==  philo->id)
		{
			pthread_mutex_lock(&philo->data->write);
			printf("%.0f %d is eating\n", get_time_stamp(philo->data), philo->id);
			pthread_mutex_unlock(&philo->data->write);
			philo->eat_count++;
			philo->data->check ++;
			philo->data->fork[philo->left] = 1;
			philo->data->fork[philo->right] = 1;
			philo->last_eat = get_time_stamp(philo->data);
			usleep(philo->data->eat_time * 1000);
			pthread_mutex_unlock(&philo->data->fork_mutex[philo->left]);
			pthread_mutex_unlock(&philo->data->fork_mutex[philo->right]);

		}

}



void* philosopher(void* arg) {
    t_ph *philo;

    philo = *(t_ph **)arg;
	philo->last_eat = get_time_stamp(philo->data);
    pthread_mutex_lock(&philo->data->start);
    pthread_mutex_unlock(&philo->data->start);
	if (philo->id % 2 == 0) 
		usleep(250000);


	while(1)
	{
		if (get_time_stamp(philo->data) - philo->last_eat > philo->data->life_time)
		{
			printf("%.0f %d died\n", get_time_stamp(philo->data), philo->id);

			break;
		}
		if (philo->eat_count == philo->data->must_eat && philo->eat_count != 0)
			break ;
		philo_eating(philo);
			pthread_mutex_lock(&philo->data->write);
		printf("%.0f %d is sleeping\n", get_time_stamp(philo->data), philo->id);
			pthread_mutex_unlock(&philo->data->write);
		usleep(philo->data->sleep_time * 1000);
			pthread_mutex_lock(&philo->data->write);

		printf("%.0f %d is thinking\n", get_time_stamp(philo->data), philo->id);
			pthread_mutex_unlock(&philo->data->write);

	}

    return (arg);
}

int init_data(char **argv , int argc, t_data *data)
{
    data->num = ft_atoi(argv[1]);
    data->life_time = ft_atoi(argv[2]);
    data->eat_time = ft_atoi(argv[3]);
    data->sleep_time = ft_atoi(argv[4]);
    data->must_eat = 0; // check
    if (argc == 6)
        data->must_eat = ft_atoi(argv[5]);

    int i = 1;
    data->philo  = ft_calloc(data->num + 2, sizeof(t_ph *));

    pthread_mutex_init(&data->write, NULL);
    pthread_mutex_init(&data->start, NULL);

	gettimeofday(&(data->time), NULL);

	data->start_time = data->time.tv_sec * 1000 + data->time.tv_usec / 1000;
	data->fork = ft_calloc(data->num + 2, sizeof(int)); 
	data->fork_mutex = ft_calloc(data->num + 2, sizeof(pthread_mutex_t));
    for (i = 1; i <= data->num; i++) {
		data->fork[i] = 1;
		// data->fork_mutex = calloc(data->num, sizeof(pthread_mutex_t));
        pthread_mutex_init(&data->fork_mutex[i], NULL);
    }

    for (i = 1; i <= data->num; i++)
    {
        data->philo[i] = calloc(1, sizeof(t_ph));
        data->philo[i]->id = i;
        data->philo[i]->right = i;
        data->philo[i]->left = i % data->num + 1;
        data->philo[i]->data = data; // philo 구조체에 data 구조체 참조 설정
        data->philo[i]->eat_count = 0; // philo 구조체에 data 구조체 참조 설정
    }
    return 0;
}

void print_parsing(t_data *data)
{
    printf("num = %d\n", data->num);
    printf("life_time = %d\n", data->life_time);
    printf("eat_time = %d\n", data->eat_time);
    printf("sleep_time = %d\n", data->sleep_time);
    printf("must_eat = %d\n", data->must_eat);

    for (int i = 1; i <= data->num; i++)
    {
        printf("%d left = %d , right = %d\n", data->philo[i]->id, data->philo[i]->right, data->philo[i]->left);
        // printf("thread %ld eat_count = %d , eat_time = %d\n", data->philo[i]->thread, data->philo[i]->eat_count, data->philo[i]->eat_time);
    }
}

int main(int argc, char *argv[])
{
    t_ph *philo;
    t_data *data;

    data = calloc(1, sizeof(t_data));
    if (argc != 5 && argc != 6)
        return (1);
    if (init_data(argv, argc, data))
        return (1);

    pthread_mutex_lock(&data->start);  // 시작 뮤텍스 획득

    for(int i = 1; i <= data->num; i++) // 스레드 생생성
    {
        pthread_create(&data->philo[i]->thread, NULL, philosopher, &data->philo[i]);  // 이중 포인터 전달
    }
    pthread_mutex_unlock(&data->start);  // 시작 뮤텍스 해제

    for(int i = 1; i <= data->num; i++)
    {
        pthread_join(data->philo[i]->thread, NULL);
    }


    // 메모리 해제
    for (int i = 1; i <= data->num; i++) {
        free(data->philo[i]);
    }
    for (int i = 1; i <= data->num; i++) {
        pthread_mutex_destroy(&data->fork_mutex[i]);
    }

    free(data->philo);
    free(data->fork);
    free(data->fork_mutex);
    free(data);

    return 0;
}
