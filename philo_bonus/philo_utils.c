#include "philosophers_bonus.h"

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
		if ((get_miliseconds() - i) >= time)
			break ;
		usleep(500);
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
