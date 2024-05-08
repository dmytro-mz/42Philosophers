#include "philo_bonus.h"

int get_time_diff_ms(struct timeval gr, struct timeval lt)
{
    int time_diff_ms;

    time_diff_ms = (gr.tv_sec - lt.tv_sec) * 1000;
    time_diff_ms += (gr.tv_usec - lt.tv_usec) / 1000;
    return (time_diff_ms);
}
