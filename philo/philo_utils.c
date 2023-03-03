#include "philosophers.h"

int get_miliseconds(void)
{
	struct timeval *time;
	gettimeofday(time, NULL);
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}

int time_dif(int time1)
{
	int time2;

	time2 = get_miliseconds();
	return (time2 - time1);
}

void	arg_control(int ac, char **av)
{
	int	i;

	i = 0;
	if (!(ac == 6 || ac == 5))
	{
		printf("Error on arguments\n");
		exit(1);
	}
	while (++i < ac)
	{
		if (!ft_isnumber(av[i]))
		{
			printf("Error on arguments\n");
			exit(1);
		}
	}
}

int	ft_isnumber(char *str)
{
	int	i;

	i = -1;
	while (*(str + ++i))
		if (*(str + i) > '9' || *(str + i) < '0')
			return (0);
	return (1);
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