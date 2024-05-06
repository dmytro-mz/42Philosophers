#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h> // gettimeofday
# include <string.h>   // memset
# include <stdio.h>	// printf
# include <unistd.h>   // write, usleep
# include <stdlib.h>   // malloc, free
# include <pthread.h>  // pthread_***
# include <stddef.h>   // size_t

# define MAIN_CHECKER_SLEEP 1000

typedef struct s_state t_state;
typedef struct s_phil_cont t_phil_cont;

struct s_state
{
	int n_phils;
	int die_ms;
	int eat_ms;
	int sleep_ms;
	int total_meals;
	pthread_t *threads;
	pthread_mutex_t *mutex_forks;
	t_phil_cont *pcs;
	int is_sim_done;
};

struct s_phil_cont
{
	int i;
	int n_meals;
	struct timeval last_meal_tv;
	t_state *state;
};

//ala libft
size_t  ft_strlen(char *str);
int	 ft_atoi(const char *str);

void	parse_params(int ac, char **av, t_state *state);
void	*simulate(void * arg);
void	show_help(void);
void	init_state(t_state *state);
void	clean_n_exit(t_state *state, char *error);
void	full_clean(t_state *state);
void	log_message(int phil_n, char *msg);
int		get_time_diff_ms(struct timeval gr, struct timeval lt);
int		check_pulse(t_phil_cont *c, struct timeval now);

#endif