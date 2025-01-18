#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
    char    c;
    int     bits;
}   t_data;

static t_data g_data;

static void handle_signal(int signum, siginfo_t *info, void *context)
{
    static pid_t client_pid;
    
    (void)context;
    if (!client_pid)
        client_pid = info->si_pid;
    if (client_pid != info->si_pid)
    {
        kill(info->si_pid, SIGUSR1);
        return;
    }
    if (signum == SIGUSR1)
        g_data.c = (g_data.c << 1) | 1;
    else if (signum == SIGUSR2)
        g_data.c <<= 1;
    g_data.bits++;
    if (g_data.bits == 8)
    {
        if (g_data.c == '\0')
        {
            ft_printf("\nMessage received successfully!\n");
            kill(client_pid, SIGUSR1); 
            client_pid = 0;
            g_data.c = 0;
            g_data.bits = 0;
            return;
        }
        write(1, &g_data.c, 1);
        g_data.c = 0;
        g_data.bits = 0;
        kill(client_pid, SIGUSR2); 
    }
    else
        kill(client_pid, SIGUSR2); 
}

int main(void)
{
    struct sigaction sa;

    g_data.c = 0;
    g_data.bits = 0;
    ft_printf("Server PID: %d\n", getpid());
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
        sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_printf("Error: Failed to setup signal handlers\n");
        exit(1);
    }
    while (1)
        pause();
    return (0);
}
