#include "apue.h"

static void sig_quit(int);

int main(void)
{
	sigset_t newmask, oldmask, pendmask, testmask;
	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		err_sys("can't catch SIGQUIT");
	/*
		Block SIGQUIT and save current signal mask
	*/
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	// test
	sigprocmask(0, NULL, &testmask);
	if (sigismember(&testmask, SIGQUIT))
		printf("\nSIGQUIT is in the testmask\n");

	// test
	if (sigismember(&newmask, SIGQUIT))
		printf("\nSIGQUIT is in the newmask\n");

	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
	
	// test
	sigprocmask(0, NULL, &testmask);
	if (sigismember(&testmask, SIGQUIT))
		printf("\nSIGQUIT is in the testmask\n");

	// test
	if (sigismember(&oldmask, SIGQUIT))
		printf("\nSIGQUIT is in the oldmask\n");

	sleep(5);  // SIGQUIT here will remain pending

	if (sigpending(&pendmask) < 0)
		err_sys("sigpending error");
	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");

	// Restore signal mask which unblocks SIGQUIT
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");

	sigprocmask(0, NULL, &oldmask);

	// test
	if (sigismember(&oldmask, SIGQUIT))
		printf("\nSIGQUIT is in the oldmask\n");

	printf("SIGQUIT unblock\n");

	sleep(5);  // SIGQUIT here will terminate with core file
	exit(0);
}

static void sig_quit(int signo)
{
	printf("caught SIGQUIT\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		err_sys("can't reset SIGQUIT");
}
