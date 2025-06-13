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
	unsigned int	nphilo;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	max_eat;
}	t_args;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	unsigned int	tte;
}	t_philo;

typedef struct s_data
{
	long			t0;
	t_args			args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

//parsing.c

int parsing(int argc, char **argv, t_args *args);
void print_args(t_args args);

//clock.c

long	get_elapsed_time(struct timeval t0);
void	wait_x_ms(long x);
long	get_time_ms(void);

#endif
