#include "../inc/philo.h"

long	get_elapsed_time(struct timeval t0)
{
	long			dt;
	struct timeval	tn;

	gettimeofday(&tn, NULL);
	dt = ((tn.tv_sec - t0.tv_sec) * 1000000 + tn.tv_usec - t0.tv_usec)/1000;
	return (dt);
}

void	wait_x_ms(long x, struct timeval t0)
{
	long	tf;
	long	tx;

	tf = get_elapsed_time(t0) + x;
	do
		tx = get_elapsed_time(t0);
	while (tx < tf);
		
}

