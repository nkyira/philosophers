#include "../inc/philo.h"

void message_log(t_philo *philo, int event)
{
	pthread_mutex_lock(&philo->log->queue_lock);
	philo->log->events[philo->log->head].philo_id = philo->id;
	philo->log->events[philo->log->head].timestamp = get_time_ms() - philo->args.start_t;
	philo->log->events[philo->log->head].event = event;
	philo->log->head = (philo->log->head + 1) % MAX_EVENTS;
	pthread_mutex_unlock(&philo->log->queue_lock);
}

int think_routine(t_philo *philo, long next_death)
{
	long	hungry;

	hungry = get_time_ms() + philo->args.tte - philo->args.tts;
	message_log(philo, THINKING);
	while (hungry - get_time_ms() > 0)
	{
		if (next_death - get_time_ms() <= 0)
			return (1);
	}
	return (0);
}

int eat_routine(t_philo *philo, long *next_death, int *times_eaten)
{
	long	finish_meal;

	pthread_mutex_lock(philo->r_fork);
	message_log(philo, TOOK_FORK);
	pthread_mutex_lock(philo->l_fork);
	message_log(philo, TOOK_FORK);
	*next_death += philo->args.ttd;
	message_log(philo, EATING);
	finish_meal = get_time_ms() + philo->args.tte;
	while (finish_meal - get_time_ms() > 0)
	{
		if (next_death - get_time_ms() <= 0)
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			return (1);
		}
	}
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	(*times_eaten)++;
	if (philo->args.max_eat && philo->args.max_eat == *times_eaten)
		message_log(philo, IS_FULL);
	return (0);
}

int sleep_routine(t_philo *philo, long next_death)
{
	long	wakeup;

	message_log(philo, SLEEPING);
	wakeup = get_time_ms() + philo->args.tts;
	while (wakeup - get_time_ms() > 0)
	{
		if (next_death - get_time_ms() <= 0)
			return (1);
	}
	return (0);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	tid;
	long		next_death;
	int			times_eaten;

	philo = (t_philo *)data;
	next_death = philo->args.start_t + (long)philo->args.ttd;
	wait_x_ms(philo->args.start_t - get_time_ms());
	// printf("philo %u struct : %ld at table at time %ld\n", philo->id, philo->thread, get_time_ms() - philo->args.zero_t);
	if (philo->id % 2)
		wait_x_ms(1);
	if (philo->id)
	{
	times_eaten = 0;
	while (1)
	{
		if (eat_routine(philo, &next_death, &times_eaten))
			break;
		if (sleep_routine(philo, next_death))
			break;
		if (think_routine(philo, next_death))
			break;
	}
	}
	message_log(philo, DYING);
}
