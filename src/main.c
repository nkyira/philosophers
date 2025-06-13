#include "../inc/philo.h"

void	*routine(void *data);

t_philo create_philo(unsigned int id, pthread_mutex_t *l_fork,
					 pthread_mutex_t *r_fork, t_data *data)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, routine, &data->philos[id  - 1]);
	return (t_philo){thread, id, r_fork, l_fork, data->args.tte};
}
// make arg helper function with const
void	*routine(void *data)
{
	t_philo		philo;
	pthread_t	tid;

	tid = pthread_self();
	philo = *(t_philo *)data;
	printf("philo %u selfid : %ld at table\n", philo.id, tid);
	printf("philo %u struct : %ld at table\n", philo.id, philo.thread);
}

int main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		temp;

	if (parsing(argc, argv, &data.args))
		return (1);
	print_args(data.args);
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
		if (!i)
			temp = data.args.nphilo - 1;
		else
			temp = i - 1;
		data.philos[i] = create_philo(i + 1, &data.forks[temp], &data.forks[i], &data);
		// pthread_create(&data.philos[i].thread, NULL, routine, &data)
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
	data.t0 = get_time_ms();
	while(1)
	{
		wait_x_ms(data.args.tts);
		printf("t : %ld\n", get_time_ms() - data.t0);
	}
	free(data.philos);
	free(data.forks);
}
