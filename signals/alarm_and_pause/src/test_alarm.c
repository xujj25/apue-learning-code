#include "apue.h"

static void sig_alrm(int signo)
{
	printf("alarm!\n");
	// signal(SIGALRM, sig_alrm);
}

int main(int argc, char const *argv[])
{
	signal(SIGALRM, sig_alrm);
	int i = 5;
	while (i--)
	{
		printf("i = %d\n", i);
		printf("before setting new alarm\n");
		alarm(3);
		printf("after setting new alarm\n");
		pause();
	}
	printf("b3\n");

	alarm(0);
	return 0;
}