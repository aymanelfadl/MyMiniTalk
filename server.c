/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:02:30 by aelfadl           #+#    #+#             */
/*   Updated: 2025/01/18 21:02:32 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

static void reset_data(int *active, int *client_pid, char *c, int *bits)
{
    *c = 0;
    *bits = 0;
    *client_pid = 0;
    *active = 0;
}

static void handle_signal(int signum, siginfo_t *info, void *context)
{
    (void)context;
    static int active;
    static int client_pid;
    static char c;
    static int bits;

    if (active && client_pid != info->si_pid)
        reset_data(&active, &client_pid, &c, &bits);
    if (!active)
    {
        client_pid = info->si_pid;
        active = 1;
    }
    if (signum == SIGUSR1)
        c = (c << 1) | 1;
    else if (signum == SIGUSR2)
        c <<= 1;
    bits++;
    if (bits == 8)
    {
        if (c == '\0')
        {
            kill(client_pid, SIGUSR1);
            reset_data(&active, &client_pid, &c, &bits);
            return;
        }
        write(1, &c, 1);
        c = 0;
        bits = 0;
    }
    kill(client_pid, SIGUSR2);
}

int main(void)
{
    struct sigaction sa;

    ft_printf("Server PID: %d\n", getpid());
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || 
        sigaction(SIGUSR2, &sa, NULL) == -1)
        return (ft_printf("Error: Failed to setup signal handlers\n"), 1);
    while (1)
        pause();
    return (0);
}
