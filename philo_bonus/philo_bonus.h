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

typedef struct s_state	t_state;

struct s_state
{
	int				n_phils;
	int				die_ms;
	int				eat_ms;
	int				sleep_ms;
	int				total_meals;
	int				n_meals;
	struct timeval	last_meal_tv;
	pid_t			*children_pid;
	sem_t			*forks_access;
	sem_t			*forks;
	sem_t			*n_phil_full;
	sem_t			*g_is_sim_done;
	int				i;
	int				is_sim_done;
	int				is_all_phil_full;
};

//ala libft
size_t	ft_strlen(char *str);
int		ft_atoi(const char *str);

void	parse_params(int ac, char **av, t_state *state);
int		check_pulse(t_state *state, struct timeval now);
void	init_state(t_state *s);
void	log_message(int phil_n, char *msg);
void	show_help(void);
void	simulate(t_state *state);
int		get_time_diff_ms(struct timeval gr, struct timeval lt);
void	clean_n_raise(t_state *state, char *failed_func_name);
void	full_clean(t_state *state);
void	partial_clean(t_state *state);
void	exit_with_error(char *failed_func_name);

#endif