#include "../inc/philo.h"

long	get_elapsed_time(struct timeval t0)
{
	long			dt;
	struct timeval	tn;

	gettimeofday(&tn, NULL);
	dt = ((tn.tv_sec - t0.tv_sec) * 1000000 + tn.tv_usec - t0.tv_usec)/1000;
	return (dt);
}

long	get_time_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000000 + t.tv_usec) / 1000);
}

void	wait_x_ms(long x)
{
	long	tf;
	long	tx;

	tf = get_time_ms() + x;
	do
		tx = get_time_ms();
	while (tx < tf);
		
}

