#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

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
        usleep(5000); 
    }
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
    while (str[i])
    {
        send_msg(pid, str[i]);
        i++;
    }
    send_msg(pid, '\0');
    ft_printf("The message to PID %d: %s\n", pid, str);
    return 0;
}

