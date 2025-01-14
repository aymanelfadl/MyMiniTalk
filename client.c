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
        {
		    if ((kill(pid, SIGUSR1)) == -1)
            {
                ft_printf("ERR IN SIGUSR1!!");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if ((kill(pid, SIGUSR2)) == -1)
            {
                ft_printf("ERR IN SIGUSR1!!");
                exit(EXIT_FAILURE);
            }

        }
        usleep(500); 
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        int i;
     
        i = 0;
        while (argv[2][i])
        {
            send_msg(ft_atoi(argv[1]), argv[2][i]);
            i++;
        }
        send_msg(ft_atoi(argv[1]), '\0');
        return 0;     
    }
    else
    {
        ft_printf("Usage: %s <PID> <message>\n", argv[0]);
        return 1;
    }
}

