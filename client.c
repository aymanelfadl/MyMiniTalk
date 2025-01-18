/* client.c */
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
    int received;
    int busy;
}   t_data;

static t_data g_data;

static void handle_int(int signum)
{
    (void)signum;
    ft_printf("\nTransmission interrupted. Exiting...\n");
    exit(0);
}

static void handle_response(int signum, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;
    
    if (signum == SIGUSR1)
    {
        if (!g_data.received) // If we haven't received any acknowledgment yet
        {
            g_data.busy = 1;  // Server is busy with another client
            return;
        }
        ft_printf("\nMessage transmitted successfully!\n");
        exit(0);
    }
    else if (signum == SIGUSR2)
        g_data.received = 1;
}

static int wait_response(void)
{
    int timeout;

    timeout = 0;
    while (!g_data.received && !g_data.busy)
    {
        if (timeout++ > 1000)
        {
            ft_printf("Error: Server not responding\n");
            return (-1);
        }
        usleep(100);
    }
    
    if (g_data.busy)
    {
        ft_printf("Error: Server is busy with another client. Please try again later.\n");
        return (-1);
    }
    
    return (0);
}

static int send_char(char c, pid_t server_pid)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        g_data.received = 0;
        if ((c >> bit) & 1)
            kill(server_pid, SIGUSR1);
        else
            kill(server_pid, SIGUSR2);
        
        if (wait_response() == -1)
            return (-1);
        bit--;
    }
    return (0);
}

int main(int argc, char *argv[])
{
    struct sigaction sa;
    pid_t server_pid;
    int i;

    if (argc != 3)
    {
        ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
        exit(1);
    }
    server_pid = atoi(argv[1]);
    if (server_pid <= 0)
    {
        ft_printf("Error: Invalid server PID\n");
        exit(1);
    }

    // Initialize data
    g_data.received = 0;
    g_data.busy = 0;

    // Set up SIGINT handler
    signal(SIGINT, handle_int);

    // Set up response handlers
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handle_response;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
        sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_printf("Error: Failed to setup signal handlers\n");
        exit(1);
    }

    ft_printf("Sending message to server (PID: %d)...\n", server_pid);
    i = 0;
    while (argv[2][i])
    {
        if (send_char(argv[2][i], server_pid) == -1)
            exit(1);
        i++;
    }
    send_char('\0', server_pid);
    
    // Wait for final acknowledgment
    usleep(1000);
    return (0);
}
