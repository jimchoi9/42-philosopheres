
#include "philo.h"

#define N 5  // 철학자 수
#define LEFT(i) ((i + N - 1) % N)
#define RIGHT(i) ((i + 1) % N)
pthread_mutex_t mutex[5];
pthread_mutex_t start;

int cnt = 0;



typedef struct Philosopher {
    int id;
} Philosopher;

void think(Philosopher* p)
{
	printf("%d is thinking\n",p->id);
}
void eat(Philosopher* p)
{
	printf("%d is eating\n", p->id);
}
void take_forks(Philosopher* p) {
    pthread_mutex_lock(&mutex[p->id]);  // 왼쪽 포크 뮤텍스 획득
	printf("%d is taking left forks\n",p->id);
    pthread_mutex_lock(&mutex[RIGHT(p->id)]);  // 오른쪽 포크 뮤텍스 획득
	printf("%d is taking right forks\n",p->id);
}

void put_forks(Philosopher* p) {
    pthread_mutex_unlock(&mutex[p->id]);  // 왼쪽 포크 뮤텍스 반환
    pthread_mutex_unlock(&mutex[RIGHT(p->id)]);  // 오른쪽 포크 뮤텍스 반환
}

void* philosopher(void* arg) {
    pthread_mutex_lock(&start);  // 왼쪽 포크 뮤텍스 획득
    pthread_mutex_unlock(&start);  // 오른쪽 포크 뮤텍스 
    Philosopher* p = (Philosopher*)arg;
	int i = 0;
	if (p->id % 2 == 0)
		usleep(100000);
    while (i < 6) {
        take_forks(p);
        eat(p);
		i++;
        put_forks(p);
		usleep(100000);
        think(p);
    }
	printf("done %d\n", p->id);
	return (arg);
}

//  철학자의 수, 철학자의 수명, 밥을 먹는데 걸리는 시간, 잠자는 시간, [각 철학자가 최소한 밥을 먹어야 하는 횟수]

int init_data(char **argv , int argc, t_data *data)
{
	data->num = ft_atoi(argv[1]);
	data->life_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->must_eat = 0; // check
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);


	int i=1;
	data->philo  = ft_calloc(data->num  + 1, sizeof(t_ph *));
	// data->fork = ft_calloc(data->num, sizeof(pthread_mutex_t)); 
	while (i <= data->num)
	{
		data->philo[i] = ft_calloc(1, sizeof(t_ph));
		data->philo[i]->id = i;
		data->philo[i]->right = i;
		data->philo[i]->left = i % data->num + 1;
		i++;
	}
	return 0;

}

int main(int argc, char *argv[])
{
	t_ph *philo;
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (argc != 5 && argc != 6)
		return (1);
	if (init_data(argv, argc, data))
		return (1);
	printf("num = %d\n", data->num);
	printf("life_time = %d\n", data->life_time);
	printf("eat_time = %d\n", data->eat_time);
	printf("sleep_time = %d\n", data->sleep_time);
	printf("must_eat = %d\n", data->must_eat);


	for (int i = 1; i <= data->num; i++)
	{
		printf("%d left = %d , right = %d\n", data->philo[i]->id, data->philo[i]->right, data->philo[i]->left);
		printf("thread %d eat_count = %d , eat_time = %d\n", data->philo[i]->thread, data->philo[i]->eat_count, data->philo[i]->eat_time);
	}
	// for(int i = 0; i < 5; i++)
	// {
	// 	pthread_mutex_init(&mutex[i],NULL);
	// 	philosophers[i].id = i;
		
	// }
	// for(int i = 0; i < 5; i++)
	// {

    // pthread_mutex_lock(&start);  // 왼쪽 포크 뮤텍스 획득
	// 	pthread_create(&thread[i], NULL, philosopher, &philosophers[i]);
    // pthread_mutex_unlock(&start);  // 오른쪽 포크 뮤텍스 반환
		
	// }
	// for(int i = 0; i < 5; i++)
	// {
	// 	pthread_join(thread[i], NULL);
		
	// }
	// for(int i = 0; i < 5; i++)
	// {
	// 	pthread_mutex_destroy(&mutex[i]);
	/*
	1 = 1, 2
	2 = 2, 3 i % 5 + 1
	3 = 3, 4
	4 = 4, 5
	5 = 5, 1  

	*/
	// }

	printf("done !\n");

}

