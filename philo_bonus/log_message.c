#include "philo_bonus.h"

void log_message(int phil_n, char *msg)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("%.10ld%.3ld %d %s\n", tv.tv_sec, tv.tv_usec / 1000, phil_n, msg);
}
