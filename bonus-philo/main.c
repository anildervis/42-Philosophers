#include "philosophers_bonus.h"

int main(int argc, char **argv)
{
    // argccontrol -> 5 or 6, all positive numbers, max_eat <= 0 error
    t_args *args;

    args = (t_args *)malloc(sizeof(t_args));
    args->number_of_philo = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    args->max_eat = 0;
    if (argc == 6)
        args->max_eat = ft_atoi(argv[5]);
    args->philo = (t_philo **)malloc(sizeof(t_philo) * args->number_of_philo);
    int i = -1;
    pid_t pid;
    args->forks = sem_open("forks", O_CREAT, 0666, args->number_of_philo);
    args->report = sem_open("report", O_CREAT, 0666, 1);
    args->destoy_all = sem_open("destroy_all", O_CREAT, 0666, 1);
    args->starting_time = get_miliseconds();
    while (++i < args->number_of_philo)
    {
        args->philo[i]->id = i;
        args->philo[i]->is_eating = 0;
        args->philo[i]->last_meal_time = get_miliseconds();
        args->philo[i]->meal_count = 0;
        args->philo[i]->args = args;
    }
    i = -1;
    sem_wait(args->destoy_all);
    while (++i < args->number_of_philo)
    {
        pid = fork();
        while (pid == 0)
        {
            args->philo[i]->pid = pid;
            eat_sleep_think(args->philo[i]);
            exit(0);
        }
    }
    pthread_t check;
    pthread_create(&check, NULL, dead_check, (void *)args);
    pthread_detach(check);
    sem_wait(args->destoy_all);
    terminate_process(args);
}

void *dead_check(void *x)
{
    t_args *args;

    args = (t_args *)x;
    while(1)
    {
        int i = -1;
        int count = 0;
        while (++i < args->number_of_philo)
        {
            if (get_miliseconds() - args->philo[i]->last_meal_time > args->time_to_die)
            {
                write_situation(PRINT_DIE, args->philo[i]);
                sem_post(args->destoy_all);
            }
            if (args->max_eat != 0 && args->philo[i]->meal_count >= args->max_eat)
                count++;
        }
        if (count == args->number_of_philo)
            sem_post(args->destoy_all);
        usleep(100);
    }
    return NULL;
}

void terminate_process(t_args *args)
{
    int i = -1;

    while (++i < args->number_of_philo)
        kill(args->philo[i]->pid, SIGKILL);
    sem_close(args->forks);
    sem_close(args->destoy_all);
    sem_close(args->report);
    exit(0);
}