/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   philo.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 09:52:33 by jodavis        #+#    #+#                */
/*   Updated: 2025/06/19 09:53:49 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# define MAX_EVENTS 64

//structures

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	TOOK_FORK,
	IS_FULL,
	DYING
}	t_state;

typedef struct s_args
{
	long			zero_t;
	long			start_t;
	unsigned int	nphilo;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	max_eat;
}	t_args;

typedef struct s_event
{
	unsigned int	philo_id;
	unsigned int	event;
	long			timestamp;
}	t_event;

typedef struct s_log
{
	pthread_mutex_t	queue_lock;
	int				stop;
	int				head;
	int				tail;
	t_event			events[MAX_EVENTS];
}	t_log;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	t_log			*log;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_args			args;
}	t_philo;

typedef struct s_data
{
	t_args			args;
	t_log			log;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

//parsing.c

int		parsing(int argc, char **argv, t_args *args);
void	print_args(t_args args);

//setup.c

int		setup(t_data *data);

//clock.c

void	wait_x_ms(long x);
long	get_time_ms(void);

//philo.c

void	*routine(void *data);

//philo.c

int		sim_stop(t_log *log);
void	message_log(t_philo *philo, int event);
void	handle_events(t_log *log, int nphilo);
int		print_states(t_event event);

#endif
