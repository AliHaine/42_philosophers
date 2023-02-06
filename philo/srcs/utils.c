#include "../philo.h"

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