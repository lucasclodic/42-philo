#include <stdio.h>
#include "../includes/philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	printf("%ld\n", tv.tv_sec);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


int main()
{
	printf("%lld\n", get_time_in_ms());
}