#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>    // memset
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free, exit
# include <unistd.h>    // write, usleep, fork
# include <signal.h>    // kill
# include <pthread.h>   // pthread_***
# include <sys/time.h>  // gettimeofday
# include <sys/wait.h>  // waitpid
# include <fcntl.h>     // For O_* constants
# include <semaphore.h> // sem_open, 

typedef struct s_state t_state;

struct s_state
{
	int         n_phils;
	int         die_ms;
	int         eat_ms;
	int         sleep_ms;
	int         total_meals;
    pid_t       *children_pid;
    sem_t       *forks_access;
    sem_t       *forks;
    sem_t       *n_phil_full;
    int         is_simulation_done;
    int         i;
};

//ala libft
size_t  ft_strlen(char *str);
int	 ft_atoi(const char *str);

void    parse_params(int ac, char **av, t_state *state);

#endif