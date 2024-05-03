#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h> // gettimeofday
# include <string.h>   // memset
# include <stdio.h>    // printf
# include <unistd.h>   // write, usleep
# include <stdlib.h>   // malloc, free
# include <pthread.h>  // pthread_***

typedef struct s_state
{
    int i;
    int n;
    pthread_t *threads;
    int is_sim_done;
}       t_state;

typedef struct s_phil_cont
{
    int i;
    t_state *s;
} t_phil_cont;


void parse_params(int ac, char **av, t_state *s);
void *simulate(void * arg);

#endif