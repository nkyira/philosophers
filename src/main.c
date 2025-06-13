#include "../inc/philo.h"

// make philo helper function
// make arg helper function with const
void	*routine(void *data)
{
	pthread_t	tid;
	t_data		*ndata;
	int			i;

	ndata = (t_data *)data;
	tid = pthread_self();
	i = 0;
	while (tid != ndata->philos[i].thread)
		i++;
	ndata->philos[i].id = i + 1;
	ndata->philos[i].r_fork = &ndata->forks[i];
	if (!i)
		ndata->philos[i].l_fork = &ndata->forks[ndata->args.nphilo - 1];
	else
		ndata->philos[i].l_fork = &ndata->forks[i - 1];
	printf("philo %u %ld sits at table\n", ndata->philos[i].id, tid);
	i = 0;
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
	data.forks = malloc(sizeof(pthread_mutex_t) * data.args.nphilo);
	while (i < data.args.nphilo)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		printf("address of fork %d : %p\n", i + 1, &data.forks[i]);
		i++;
	}
	i = 0;
	while (i < data.args.nphilo)
	{
		pthread_create(&data.philos[i].thread, NULL, routine, &data);
		// wait_x_ms(data.args.tts, data.time_0);
		i++;
	}
	i = 0;
	while (i < data.args.nphilo)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data.args.nphilo)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		printf("philo %u r_fork adress is %p\n", data.philos[i].id, data.philos[i].r_fork);
		printf("philo %u l_fork adress is %p\n", data.philos[i].id, data.philos[i].l_fork);
		i++;
	}
	free(data.philos);
	free(data.forks);
}
