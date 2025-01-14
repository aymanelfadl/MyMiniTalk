#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"
#include <stdlib.h>

void send_msg(int pid, char c)
{
    int i = 8;
    unsigned char tmp;

    tmp = 0;
    while (i > 0)
    {
        i--;
 	    tmp = c >> i; 
        if (tmp % 2 == 0) 
		    kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100); 
    }
}

void stop_signal()
{
    
    ft_printf("\n You can't stop me brother");
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        ft_printf("Usage: %s <PID> <message>\n", argv[0]);
        return 1;
    }
    int pid = ft_atoi(argv[1]);
    char *str = argv[2];
    int i = 0;
    signal(SIGINT, stop_signal);
    while (str[i])
    {
        send_msg(pid, str[i]);
        i++;
    }
    send_msg(pid, '\0');
    return 0;
}

