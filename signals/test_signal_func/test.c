#include <stdio.h>
#include <signal.h>
#include <unistd.h>
// #include "apue.h"

static void sig_int(int signo)
{
    printf("get SIGINT\n");
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, sig_int);
    for (int i = 0; i < 5;  i ++)
    {
        kill(getpid(), SIGINT);
    }
    return 0;
}
