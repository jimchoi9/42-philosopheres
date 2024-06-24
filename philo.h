#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft_src/libft.h"
struct s_data;

typedef struct s_ph
{
    int id;
    int eat_count;
    int left;
    int right;
    int eat_time;
    pthread_t thread;
   struct s_data *data;
}t_ph;

typedef struct s_data
{
    int num;
    int life_time;
    int eat_time;
    int eat_count;
    int sleep_time;
    int must_eat;
    pthread_mutex_t **fork;
    pthread_mutex_t write;
    pthread_mutex_t dead;
    pthread_mutex_t start;
	t_ph **philo;
}t_data;
