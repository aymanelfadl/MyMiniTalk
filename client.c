/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:00:02 by aelfadl           #+#    #+#             */
/*   Updated: 2025/01/15 11:22:34 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	send_msg(int pid, char c)
{
	int				i;

	i = 8;
	while (i > 0)
	{
		i--;
		if ((((unsigned char)c >> i) % 2) == 0)
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
				ft_printf("ERR IN SIGUSR2 ");
				exit(EXIT_FAILURE);
			}
		}
		usleep(800);
	}
}

int	is_valid_pid(const char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void no_stop(int signum)
{
	(void)signum;
}
void setup_stop_signals(void)
{
    signal(SIGABRT, no_stop);    // Abort signal
    signal(SIGINT, no_stop);     // Interrupt (Ctrl+C)
    signal(SIGQUIT, no_stop);    // Quit (Ctrl+\)
    signal(SIGTERM, no_stop);    // Termination signal
    signal(SIGHUP, no_stop);     // Hangup
    signal(SIGALRM, no_stop);    // Alarm
    signal(SIGVTALRM, no_stop);  // Virtual timer
    signal(SIGPROF, no_stop);    // Profiling timer
    signal(SIGUSR1, no_stop);    // User defined signal 1
    signal(SIGUSR2, no_stop);    // User defined signal 2
    signal(SIGPIPE, no_stop);    // Broken pipe
}

int	main(int argc, char *argv[])
{
	int	i;
	setup_stop_signals();
	if (argc == 3)
	{
		i = 0;
		if (!is_valid_pid(argv[1]))
		{
			ft_printf("Error: Invalid PID\n");
			return (1);
		}
		while (argv[2][i])
		{
			send_msg(ft_atoi(argv[1]), argv[2][i]);
			i++;
		}
		send_msg(ft_atoi(argv[1]), 0);
		return (0);
	}
	else
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (1);
	}
}
