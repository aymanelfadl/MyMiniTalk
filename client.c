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
	struct sigaction sa;
	sigset_t mySet;

	sigfillset(&mySet);

	sigdelset (&mySet, SIGUSR1);
	sigdelset (&mySet, SIGUSR2);

	sa.sa_handler = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 

	sa.sa_mask = mySet;
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
		usleep(1000);
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

int	main(int argc, char *argv[])
{
	int	i;

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
