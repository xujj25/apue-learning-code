#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo)
{
	printf("get into sig_alrm function\n");
	longjmp(env_alrm, 1);
}

unsigned int sleep2(unsigned int seconds)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return(seconds);
	if (setjmp(env_alrm) == 0) {
		alarm(seconds);  // start the timer
		pause();  //next caught signal wakes us up
	}

	// test
	alarm(1);
	signal(SIGALRM, sig_alrm);
	printf("finished setting new alarm\n");


	// pause();
	return(0);  // turn off timer, return unslept time
}