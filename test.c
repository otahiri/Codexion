#include "codexion.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	long	start;

	start = get_time(0);
	printf("time is %ld", get_time(start));
	usleep(atoi(argv[1]) * 1000);
	printf("time is %ld", get_time(start));
}
