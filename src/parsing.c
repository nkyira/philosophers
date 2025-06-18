#include "../inc/philo.h"

static void print_parse_err(int type)
{
	if (type == 1)
		printf("usage: ./philo <num_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> <(optional)number_of_times_each_philo_must_eat>\n");
	if (type == 2)
		printf("enter values as unsigned integers ranging from 0 to 2147483647\n");
}

void print_args(t_args args)
{
	printf("number of philos : %u\n", args.nphilo);
	printf("time to die : %u\n", args.ttd);
	printf("time to eat : %u\n", args.tte);
	printf("time to sleep : %u\n", args.tte);
	printf("number of times to eat : %u\n", args.max_eat);
	printf("zero_t : %ld\n", args.zero_t);
	printf("start_t : %ld\n", args.start_t);
}

static int all_num(char **argv)
{
	int i;

	while(*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			if ((*argv)[i] < '0' || (*argv)[i] > '9')
				return (0);
			i++;
		}
		argv++;
	}
	return (1);
}

int parsing(int argc, char **argv, t_args *args)
{
	if(argc != 5 && argc != 6)
	{
		print_parse_err(1);
		return (1);
	}
	if(!all_num(++argv))
	{
		print_parse_err(2);
		return (1);
	}
	args->nphilo = (unsigned int)atoi(*(argv++));
	args->ttd = (unsigned int)atoi(*(argv++));
	args->tte = (unsigned int)atoi(*(argv++));
	args->tts = (unsigned int)atoi(*(argv++));
	args->zero_t = get_time_ms();
	args->start_t = args->zero_t + args->nphilo;
	if (*argv)
		args->max_eat = (unsigned int)(atoi(*argv));
	else
		args->max_eat = 0;
	return (0);
}
