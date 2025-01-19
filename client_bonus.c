/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:02:10 by aelfadl           #+#    #+#             */
/*   Updated: 2025/01/18 21:02:22 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	g_done;

static	void	handle_response(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
	{
		ft_printf("Message transmitted successfully!\n");
		exit(0);
	}
	else if (signum == SIGUSR2)
		g_done = 1;
}

static	int	wait_response(void)
{
	int			timeout;
	static int	i;

	timeout = 0;
	while (!g_done)
	{
		if (timeout++ > 1000)
			return (ft_printf("Error: Server not responding\n"), -1);
		usleep(100);
	}
	if (!i)
		i = 1;
	ft_printf("Received %d\n", i++);
	return (0);
}

static	int	send_char(char c, pid_t server_pid)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_done = 0;
		if ((c >> bit) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		if (wait_response() == -1)
			exit(1);
		bit--;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	struct sigaction		sa;
	int						i;

	if (argc != 3)
		return (ft_printf("Usage: %s <server_pid> <message>\n", argv[0]), 1);
	if (atoi(argv[1]) <= 0)
		return (ft_printf("Error: Invalid server PID\n"), 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_response;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_printf("Error\n"), 1);
	i = 0;
	while (argv[2][i])
		send_char(argv[2][i++], atoi(argv[1]));
	send_char('\0', atoi(argv[1]));
	return (0);
}
