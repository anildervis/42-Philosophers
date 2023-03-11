/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderviso <aderviso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:18:28 by aderviso          #+#    #+#             */
/*   Updated: 2023/03/11 19:18:28 by aderviso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_miliseconds(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	time_dif(int time1)
{
	return (get_miliseconds() - time1);
}

void	u_sleep(long long time)
{
	long long	i;

	i = get_miliseconds();
	while (1)
	{
		if (time_dif(i) >= time)
			break ;
		usleep(500);
	}
}

void	arg_control(int ac, char **av)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (!(ac == 6 || ac == 5))
	{
		printf("Error on arguments\n");
		exit(1);
	}
	while (++i < ac)
	{
		k = -1;
		while (*(av[i] + ++k))
		{
			if (*(av[i] + k) > '9' || *(av[i] + k) < '0')
			{
				printf("Error on arguments\n");
				exit(1);
			}
		}
	}
}

int	ft_atoi(char *str)
{
	long long	nbr;
	int			i;

	i = -1;
	nbr = 0;
	while (*(str + ++i))
		nbr = nbr * 10 + (*(str + i) - '0');
	return (nbr);
}
