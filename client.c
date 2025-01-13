#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

void ft_no_stop(int signum)
{

    ft_printf("the %d wait",signum);
}


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

int main(int argc, char *argv[])
{

    struct sigaction sa;

    sa.sa_handler = ft_no_stop;
    sigemptyset(&sa.sa_mask);     
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        ft_printf("Failed to set up SIGINT handler.\n");
        return 1;
    }
    if (argc != 3)
    {
        ft_printf("Usage: %s <PID> <message>\n", argv[0]);
        return 1;
    }
    int pid = ft_atoi(argv[1]);
    char *str = argv[2];
    int i = 0;

    while (str[i])
    {
        send_msg(pid, str[i]);
        i++;
    }
    send_msg(pid, '\0');
    ft_printf("The message to PID %d: %s\n", pid, str);
    return 0;
}

