/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   events.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 09:58:02 by jodavis        #+#    #+#                */
/*   Updated: 2025/06/19 10:06:05 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	sim_stop(t_log *log)
{
	int	stop;

	pthread_mutex_lock(&log->queue_lock);
	stop = log->stop;
	pthread_mutex_unlock(&log->queue_lock);
	return (stop);
}

void	message_log(t_philo *philo, int event)
{
	pthread_mutex_lock(&philo->log->queue_lock);
	philo->log->events[philo->log->head].philo_id = philo->id;
	philo->log->events[philo->log->head].timestamp
		= get_time_ms() - philo->args.start_t;
	philo->log->events[philo->log->head].event = event;
	philo->log->head = (philo->log->head + 1) % MAX_EVENTS;
	pthread_mutex_unlock(&philo->log->queue_lock);
}

static int	all_full(t_log *log, int nphilo, int *full_philos)
{
	(*full_philos)++;
	if (*full_philos == nphilo)
	{
		log->stop = 1;
		pthread_mutex_unlock(&log->queue_lock);
		return (1);
	}
	return (0);
}

void	handle_events(t_log *log, int nphilo)
{
	int	full_philos;
	int	state;

	full_philos = 0;
	while (1)
	{
		while (log->head != log->tail)
		{
			pthread_mutex_lock(&log->queue_lock);
			state = print_states(log->events[log->tail]);
			if (state == 1)
			{
				log->stop = 1;
				pthread_mutex_unlock(&log->queue_lock);
				return ;
			}
			if (state == 2)
			{
				if (all_full(log, nphilo, &full_philos))
					return ;
			}
			log->tail = (log->tail + 1) % MAX_EVENTS;
			pthread_mutex_unlock(&log->queue_lock);
		}
	}
}

int	print_states(t_event event)
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
		return (1);
	}
	if (event.event == IS_FULL)
		return (2);
	return (0);
}
