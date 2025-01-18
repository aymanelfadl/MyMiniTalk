/* server.c */
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
    char    c;
    int     bits;
    pid_t   client_pid;
    int     active;
}   t_data;

static t_data g_data;

static void reset_data(void)
{
    g_data.c = 0;
    g_data.bits = 0;
    g_data.client_pid = 0;
    g_data.active = 0;
}

static void handle_signal(int signum, siginfo_t *info, void *context)
{
    (void)context;

    if (g_data.active && g_data.client_pid != info->si_pid)
    {
        kill(info->si_pid, SIGUSR1);
        return;
    }
    if (!g_data.active)
    {
        g_data.client_pid = info->si_pid;
        g_data.active = 1;
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
            kill(g_data.client_pid, SIGUSR1);
            reset_data();
            return;
        }
        write(1, &g_data.c, 1);
        g_data.c = 0;
        g_data.bits = 0;
    }
    kill(g_data.client_pid, SIGUSR2);
}

int main(void)
{
    struct sigaction sa;

    reset_data();
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
