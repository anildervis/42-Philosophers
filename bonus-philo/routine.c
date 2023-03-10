#include "philosophers_bonus.h"

void eat_sleep_think(t_philo *philo)
{
    pthread_t check;

    pthread_create(&check, NULL, dead_check, (void *)philo);
    pthread_detach(check);
    while (1)
    {
        eat(philo);
        write_situation(PRINT_THINK, philo);
    }
}

void *dead_check(void *x)
{
    t_philo *philo;

    philo = (t_philo *)x;
    while(1)
    {
        int count = 0;
        if ((get_miliseconds() - philo->last_meal_time) > philo->args->time_to_die)
        {
            write_situation(PRINT_DIE, philo);
            sem_post(philo->args->destoy_all);
        }
        else if (philo->args->max_eat != 0 && philo->meal_count >= philo->args->max_eat)
        {
            sem_post(philo->args->meal_check);
            usleep(10000000);
        }
        usleep(100);
    }
    return NULL;
}

void eat(t_philo *philo)
{
    sem_wait(philo->args->forks);
    write_situation(PRINT_FORK, philo);
    sem_wait(philo->args->forks);
    write_situation(PRINT_FORK, philo);
    write_situation(PRINT_EAT, philo);
    philo->last_meal_time = get_miliseconds();
    philo->meal_count++;
    u_sleep(philo->args->time_to_eat);
    sem_post(philo->args->forks);
    sem_post(philo->args->forks);
    write_situation(PRINT_SLEEP, philo);
    u_sleep(philo->args->time_to_sleep);
}

void write_situation(int type, t_philo *philo)
{
    sem_wait(philo->args->report);
    printf("%d %d ", time_dif(philo->args->starting_time), philo->id + 1);
    if (type == PRINT_FORK)
        printf("has taken a fork\n");
    else if (type == PRINT_EAT)
        printf("is eating\n");
    else if (type == PRINT_SLEEP)
        printf("is sleeping\n");
    else if (type == PRINT_THINK)
        printf("is thinking\n");
    else
        printf("died\n");
    sem_post(philo->args->report);
}