#include <stdio.h>
#include "../includes/philo.h"

// int ft_atoi(char *str)
// {
// 	int i;
// 	long int output; 

// 	if (!str)
// 		return 0; 
//     i = 0; 
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
// 	output = 0;
// 	while (str[i] && (str[i] >= '0' || str[i] <= '9'))
// 	{
// 		output = output * 10 + str[i] - '0';
// 		i++;
// 	}
// 	return (output);
// }

// int main(int argc, char **argv)
// {
// 	if (argc < 2)
// 		return (0);
// 	else
// 	{
// 		int output = ft_atoi(argv[1]);
// 		printf("end [%d]\n", output);
// 	}
// }

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


int main()
{
	printf("%lld\n", get_time_in_ms());
}