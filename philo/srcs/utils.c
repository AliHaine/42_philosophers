#include "../philo.h"

long long current_timestamp() {
	struct timeval te;
	gettimeofday(&te, NULL); // get current time
	long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
	// printf("milliseconds: %lld\n", milliseconds);
	return milliseconds;
}

static bool is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (true);
    return (false);
}

int ft_atoi(char *argv)
{
    int             i;
    long long int   result;

    i = 0;
    result = 0;
    while (argv[i])
    {
        if (is_digit(argv[i]) == false)
            return (0);
        result = (result * 10) + (argv[i] - '0');
        i++;
    }
    if (result > 2147483647)
        return (0);
    return (result);
}

static int	get_power(int i)
{
	int o;

	o = 10;
	while (i > 0)
	{
		o = o * 10;
		i--;
	}
	return (o / 10);
}

char *ft_itoa(int i)
{
	int size;
	int save;
	char *str;
	int o;

	size = 1;
	save = i;
	o = 0;
	while (save > 9)
	{
		save /= 10;
		size++;
	}
	str = malloc(sizeof(char) * size + 1);
	while (i > 9)
	{
		str[o] = (i / get_power(size - 1) + '0');
		i /= 10;
		size--;
		o++;
	}
	str[o] = i + '0';
	str[o + 1] = 0;
	return (str);
}

void    fff(pthread_mutex_t *mutex, t_philo *philo)
{
	pthread_mutex_lock(mutex);


	if (philo->id == 0)
		printf("ID %d, Fork %p, Prev Fork %p, Prev Philo %p\n", philo->id, &philo->fork, &philo[philo->rules->nbr_philo - 1].fork, philo);
	else
		printf("ID %d, Fork %p, Prev Fork %p, Prev Philo %p\n", philo->id, &philo->fork, &philo[philo->id - 1].fork, &philo[(philo->id - 1)]);
	pthread_mutex_unlock(mutex);
}


void    put_str(int ms, int id, char *str, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
    int i;
	char *conv;

    i = 0;
	conv = ft_itoa(ms);
	while (conv[i])
	{
		write(1, &conv[i], 1);
		i++;
	}
	write(1, " ", 1);
	i = 0;
	conv = ft_itoa(id);
	while (conv[i])
	{
		write(1, &conv[i], 1);
		i++;
	}
	i = 0;
	write(1, " ", 1);
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
	pthread_mutex_unlock(mutex);
}