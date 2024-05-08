#include "philo.h"

void init_state(t_state *state)
{
	int i;
	struct timeval now;
	pthread_mutexattr_t attr;

	state->threads = malloc(sizeof(pthread_t) * state->n_phils);
	state->mutex_forks = malloc(sizeof(pthread_mutex_t) * state->n_phils);
	state->pcs = malloc(sizeof(t_phil_context) * state->n_phils);
	if (!(state->threads && state->mutex_forks && state->pcs))
		clean_n_exit(state, "malloc");
	gettimeofday(&now, NULL);
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	i = 0;
	while (i < state->n_phils)
	{
		if (pthread_mutex_init(state->mutex_forks + i, &attr) != 0)
			clean_n_exit(state, "pthread_mutex_init");
		state->pcs[i].i = i;
		state->pcs[i].state = state;
		state->pcs[i].n_meals = 0;
		state->pcs[i].last_meal_tv = now;
		i++;
	}
	state->is_sim_done = 0;
	pthread_mutexattr_destroy(&attr);
}
