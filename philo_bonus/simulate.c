#include "philo_bonus.h"

void    simulate(t_state *state)
{
    p_thread_t  th;

    gettimeofday(&state->last_meal_tv, NULL);
    if (pthread_create(&th, NULL, &is_phil_alive, state) != 0)
        exit_with_error("pthread_create");
	while (!state->is_sim_done)
	{
		eat(state, &th);
        if (!state->is_sim_done)
        {
            log_message(state->i, "is sleeping");
            usleep(state->sleep_ms * 1000);
        }
        if (!state->is_sim_done)
            log_message(state->i, "is thinking");
	}
    if (pthread_join(&th, NULL) != 0)
        exit_with_error("pthread_join");
    exit(0);
}

void eat(t_state *state, p_thread_t  *th)
{
    struct timeval now;

    sem_wait(state->forks_access);
    sem_wait(state->forks);
    if (!state->is_sim_done)
	    log_message(state->i, "has taken a fork");
    if (state->n_phils == 1)
    {
        while (!state->is_sim_done)
            usleep(1000);
        return ;
    }
    sem_wait(state->forks);
    if (!state->is_sim_done)
	    log_message(state->i, "has taken a fork");
    sem_post(state->forks_access);
    gettimeofday(&now, NULL);
    if (check_pulse(state, now))
        return ;
    state->last_meal_tv = now;
    log_message(state->i, "is eating");
    usleep(state->eat_ms * 1000);
    state->n_meals++;
    if (state->total_meals >= 0 && state->n_meals == state->total_meals)
        sem_post(state->n_phil_full);
}

void *is_phil_alive(void *arg)
{
    struct timeval  now;
    t_state         *state;

    state = (t_state *)arg;
    while (1)
    {
        gettimeofday(&now, NULL);
        if (check_pulse(state, now))
            return (NULL);
        usleep(100);
    }
}
