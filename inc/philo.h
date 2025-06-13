#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//structures

typedef struct s_args
{
	const unsigned int	nphilo;
	const unsigned int	ttd;
	const unsigned int	tte;
	const unsigned int	tts;
	const unsigned int	max_eat;
}	t_args;

typedef struct s_philo
{
	pthread_t				thread;
	const unsigned int		id;
	pthread_mutex_t *const	r_fork;
	pthread_mutex_t *const	l_fork;
}	t_philo;

typedef struct s_data
{
	struct timeval	time_0;
	t_args			args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

//parsing.c

int parsing(int argc, char **argv, t_args *args);
void print_args(t_args args);

//clock.c

long	get_elapsed_time(struct timeval t0);
void	wait_x_ms(long x, struct timeval t0);

#endif
