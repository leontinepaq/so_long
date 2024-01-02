#include <sys/time.h>
#include "includes/so_long.h"
#include <stdio.h>

int	main(void)
{
	int mill;
	int sum;
	int over_500;
	struct timeval te;
	int i = 0;
	int nb_tests = 500000;

	sum = 0;
	over_500 = 0;

    while (i < nb_tests)
	{
    	gettimeofday(&te, NULL); // get current time
    	long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
		mill = (unsigned int) milliseconds % 1000;
		sum +=mill;
		if (mill > 500)
				over_500++;
		printf("milliseconds: %u\n", (unsigned int) milliseconds % 1000);
		i++;
	}
	printf("Moyenne : %i\n", sum/nb_tests);
	printf("Pourcentage : %i\n", (over_500 * 100) / nb_tests);
	return (0);
}