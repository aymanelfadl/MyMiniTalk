/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:02:30 by aelfadl           #+#    #+#             */
/*   Updated: 2025/01/18 22:16:09 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

static	void	reset_data(int *active, int *client_pid, char *c, int *bits)
{
	*c = 0;
	*bits = 0;
	*client_pid = 0;
	*active = 0;
}

static	int	print_char(int *bits, char *c)
{
	if (*bits == 8)
	{
		if (*c == '\0')
			return (1);
		write(1, c, 1);
		*c = 0;
		*bits = 0;
	}
	return (0);
}

static	void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int	active;
	static int	client_pid;
	static char	c;
	static int	bits;

	(void)context;
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
	if (print_char(&bits, &c))
	{
		kill(client_pid, SIGUSR1);
		reset_data(&active, &client_pid, &c, &bits);
		return ;
	}
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_printf("Error\n"), 1);
	while (1)
		pause();
	return (0);
}
