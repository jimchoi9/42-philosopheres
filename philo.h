#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "./libft_src/libft.h"
typedef struct s_data t_data;

typedef struct s_ph
{
    int id;
    int eat_count;
    int left;
    int right;
	double last_eat;
    pthread_t thread;
   t_data *data;

}t_ph;

typedef struct s_data
{
	int check;
    int num;
    int life_time;
    int eat_time;
    int eat_count;
    int sleep_time;
    int must_eat;
    double start_time;
    int *fork;
    pthread_mutex_t *fork_mutex;
    pthread_mutex_t write;
    pthread_mutex_t dead;
    pthread_mutex_t start;
	t_ph **philo;
	struct timeval time;
}t_data;
