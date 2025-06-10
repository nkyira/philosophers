#include "../inc/philo.h"

void	*routine(void *data)
{
	pthread_t	tid;
	t_data		*ndata;
	int			i;

	ndata = (t_data *)data;
	tid = pthread_self();
	while (tid != ndata->philos[i].thread)
		i++;
	i++;
	printf("philo %d %ld sits at table\n", i, tid);
}

int main(int argc, char **argv)
{
	t_data	data;
	long	dt;
	int		i;

	gettimeofday(&data.time_0, NULL);
	if (parsing(argc, argv, &data.args))
		return (1);
	print_args(data.args);
	// while(1)
	// {
	// 	wait_x_ms(data.args.tts, data.time_0);
	// 	dt = get_elapsed_time(data.time_0);
	// 	printf("t : %ld\n", dt);
	// }
	i = 0;
	data.philos = malloc(sizeof(t_philo) * data.args.nphilo);
	while (i < data.args.nphilo)
	{
		pthread_create(&data.philos[i].thread, NULL, routine, &data);
		wait_x_ms(data.args.tts, data.time_0);
		i++;
	}
	i = 0;
	while (i < data.args.nphilo)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	free(data.philos);
}
