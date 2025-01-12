#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

void handler(int signum)
{
    static unsigned char c;
    static int index;

    index++;
    c |= (signum == SIGUSR2);
    if (index == 8)
    {
        if(c == '\0')
            write(1,"\n",1);
        else
            write(1, &c, 1);
        index = 0;
        c = 0;
    }
    else
        c <<= 1;
}

int main()
{
    pid_t pid = getpid();

    printf("PID: %d\n", pid);

    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    while(1)
    {
    }
    return 0;
}

