/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: jodavis <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 09:55:02 by jodavis        #+#    #+#                */
/*   Updated: 2025/06/19 09:55:08 by jodavis        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (parsing(argc, argv, &data.args))
		return (1);
	if (setup(&data))
		return (1);
	handle_events(&data.log, data.args.nphilo);
	i = 0;
	while (i < data.args.nphilo)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	free(data.philos);
	free(data.forks);
}
