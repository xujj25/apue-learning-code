#include "apue.h"
#include "sleep2.h"

static void sig_int(int);

int main(void)
{
	unsigned int unslept;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	unslept = sleep2(1);
	
	/*
		the longjmp from the sleep2 function
		aborted the other signal handler, sig_int, 
		even though it wasn’t finished
	*/
	printf("sleep2 returned: %u\n", unslept);

	//test
	pause();

	exit(0);
}

static void sig_int(int signo)
{
	int i, j;
	volatile int k;
	/*
	* Tune these loops to run for more than 5s
	* on whatever system this test program is run
	*/
	printf("\nsig_int starting\n");
	for (i = 0; i < 300000; i++)
	{
		for (j = 0; j < 4000; j++)
			k += i * j;
	}
	printf("sig_int finished\n");
}