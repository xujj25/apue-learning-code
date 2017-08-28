#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void sig_int(int signo)
{
    printf("sig_int function start!\n");
    int i, j;
    volatile int k;
    for (i = 1; i < 300000; i++)
        for (j = 1; j < 5000; j++)
            k += i * j;
    printf("sig_int function finish!");
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, sig_int);
    raise(SIGINT);
    printf("breakpoint 1\n");
    raise(SIGINT);
    printf("breakpoint 2\n");
    return 0;
}
