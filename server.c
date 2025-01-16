/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 23:38:14 by aelfadl           #+#    #+#             */
/*   Updated: 2025/01/14 23:45:56 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "libft/libft.h"
#include <stdio.h>

int in_prog = 1;

void	handler(int signum)
{
	static int				index;
	static unsigned char	c;

	index++;
	c |= (signum == SIGUSR2);
	if (index == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		index = 0;
		c = 0;
	}
	else
		c <<= 1;
}


int	main(void)
{
	pid_t	pid;
	struct sigaction sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	pid = getpid();
	ft_printf ("PID: %d\n", pid);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
