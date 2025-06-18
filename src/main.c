#include "../inc/philo.h"

// handle needs to take log in parameter to stop sim
// maybe return id of philos who are full

int handle(t_event event)
{
	if (event.event != IS_FULL)
		printf("%ld philo %u ", event.timestamp, event.philo_id);
	if (event.event == THINKING)
		printf("is thinking\n");
	if (event.event == TOOK_FORK)
		printf("has taken a fork\n");
	if (event.event == EATING)
		printf("is eating\n");
	if (event.event == SLEEPING)
		printf("is sleeping\n");
	if (event.event == DYING)
	{
		printf("died\n");
		return (0);
	}
	if (event.event == IS_FULL)
		printf("%ld philo %u is full\n", event.timestamp, event.philo_id);

	return (1);
}

	// i = 0;
	// while (i < data.args.nphilo)
	// {
	// 	printf("philo %u l_fork adress is %p\n", data.philos[i].id, data.philos[i].l_fork);
	// 	printf("philo %u r_fork adress is %p\n", data.philos[i].id, data.philos[i].r_fork);
	// 	i++;
	// }

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		alive;

	if (parsing(argc, argv, &data.args))
		return (1);
	print_args(data.args);
	if (setup(&data))
		return (1);
	alive = 1;
	while (alive)
	{
		while (data.log.head != data.log.tail)
		{
			pthread_mutex_lock(&data.log.queue_lock);
			alive = handle(data.log.events[data.log.tail]);
			// alive might not be need thx to log
			// sim stop var in log if sim stop then philos die
			// keep a number of philos who are full var in data if it equals
			// nphilo then sim stops
			data.log.tail = (data.log.tail + 1) % MAX_EVENTS;
			pthread_mutex_unlock(&data.log.queue_lock);
		}
	}
	i = 0;
	while (i < data.args.nphilo)
	{
		printf("i = %d", i);
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	free(data.philos);
	free(data.forks);
}
