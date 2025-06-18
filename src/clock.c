#include "../inc/philo.h"

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

