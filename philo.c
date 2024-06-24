#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
}


int main()
{
	Philosopher philosophers[5];
	pthread_t thread[5];

	for(int i = 0; i < 5; i++)
	{
		pthread_mutex_init(&mutex[i],NULL);
		philosophers[i].id = i;
		
	}
	for(int i = 0; i < 5; i++)
	{

    pthread_mutex_lock(&start);  // 왼쪽 포크 뮤텍스 획득
		pthread_create(&thread[i], NULL, philosopher, &philosophers[i]);
    pthread_mutex_unlock(&start);  // 오른쪽 포크 뮤텍스 반환
		
	}
	for(int i = 0; i < 5; i++)
	{
		pthread_join(thread[i], NULL);
		
	}
	for(int i = 0; i < 5; i++)
	{
		pthread_mutex_destroy(&mutex[i]);
		
	}

	printf("done !\n");

}