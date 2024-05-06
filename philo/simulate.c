#include "philo.h"

void eat(t_phil_cont *c);
int try_update_time(t_phil_cont *c);

void *simulate(void * arg)
{
	int i;
	t_state *state;

	i = ((t_phil_cont *)arg)->i;
	state = ((t_phil_cont *)arg)->state;
	gettimeofday(&((t_phil_cont *)arg)->last_meal_tv, NULL);
	while (!state->is_sim_done)
	{
		eat((t_phil_cont *)arg);
		if (!state->is_sim_done)
		{
			log_message(i, "is sleeping");
			usleep(state->sleep_ms * 1000);
		}
		if (!state->is_sim_done)
			log_message(i, "is thinking");
	}
	return (NULL);
}

// i % 2      first fork         sec fork
// 0               i              i + 1
// 1             i + 1              i 
//             i + (i % 2)    i + 1 - (i % 2)
void eat(t_phil_cont *c)
{
	int fork_1;
	int fork_2;

	fork_1 = (c->i + (c->i % 2)) % c->state->n_phils;
	fork_2 = (c->i + 1 - (c->i % 2)) % c->state->n_phils;
	pthread_mutex_lock(&c->state->mutex_forks[fork_1]);
	if (!c->state->is_sim_done)
		log_message(c->i, "has taken a fork");
	pthread_mutex_lock(&c->state->mutex_forks[fork_2]);
	if (!c->state->is_sim_done)
		log_message(c->i, "has taken a fork");
	if (!c->state->is_sim_done && !try_update_time(c))
	{
		log_message(c->i, "is eating");
		c->n_meals++;
		usleep(c->state->eat_ms * 1000);
	}
	pthread_mutex_unlock(&c->state->mutex_forks[fork_1]);
	pthread_mutex_unlock(&c->state->mutex_forks[fork_2]);
}

int try_update_time(t_phil_cont *c)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	if (!check_pulse(c, now))
	{
		c->last_meal_tv = now;
		return (0);
	}
	return (1);
}
