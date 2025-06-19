/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   setup.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 10:17:07 by jodavis        #+#    #+#                */
/*   Updated: 2025/06/19 10:22:09 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_mutexes(t_data *data)
{
	int		i;

	i = 0;
	pthread_mutex_init(&data->log.queue_lock, NULL);
	while (i < data->args.nphilo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

static t_philo	create_philo(unsigned int id, pthread_mutex_t *l_fork,
					pthread_mutex_t *r_fork, t_data *data)
{
	return ((t_philo){0, id, &data->log, r_fork, l_fork, data->args});
}

static void	create_philos(t_data *data)
{
	int		i;
	int		left;

	i = 0;
	while (i < data->args.nphilo)
	{
		if (!i)
			left = data->args.nphilo - 1;
		else
			left = i - 1;
		data->philos[i] = create_philo(i + 1, &data->forks[left],
				&data->forks[i], data);
		pthread_create(&data->philos[i].thread, NULL,
			routine, &data->philos[i]);
		i++;
	}
}

int	setup(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->args.nphilo);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args.nphilo);
	if (!data->forks)
	{
		free(data->philos);
		return (1);
	}
	data->log.stop = 0;
	data->log.head = 0;
	data->log.tail = 0;
	init_mutexes(data);
	create_philos(data);
	return (0);
}
