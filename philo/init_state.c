#include "philo.h"

void init_state(t_state *state)
{
	int i;
	struct timeval now;

	state->threads = malloc(sizeof(pthread_t) * state->n_phils);
	state->mutex_forks = malloc(sizeof(pthread_mutex_t) * state->n_phils);
	state->pcs = malloc(sizeof(t_phil_cont) * state->n_phils);
	if (!(state->threads && state->mutex_forks && state->pcs))
		clean_n_exit(state, "malloc");
	gettimeofday(&now, NULL);
	i = 0;
	while (i < state->n_phils)
	{
		if (pthread_mutex_init(state->mutex_forks + i, NULL) != 0)
			clean_n_exit(state, "pthread_mutex_init");
		state->pcs[i].i = i;
		state->pcs[i].state = state;
		state->pcs[i].n_meals = 0;
		state->pcs[i].last_meal_tv = now;
		i++;
	}
	state->is_sim_done = 0;
}
