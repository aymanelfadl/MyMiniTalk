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
				ft_printf("ERR IN SIGUSR1!!");
				exit(EXIT_FAILURE);
			}
		}
		usleep(500);
	}
}


int	main(int argc, char *argv[])
{
	int	i;


	// signal(SIGABRT, send_reset);
	// signal(SIGTERM, send_reset);
	// signal(SIGINT, send_reset);
	// signal(SIGKILL, send_reset);

	if (argc == 3)
	{
		i = 0;
		kill(ft_atoi(argv[1]), SIGUSR2);
		while (argv[2][i])
		{
			send_msg(ft_atoi(argv[1]), argv[2][i]);
			i++;
		}
		send_msg(ft_atoi(argv[1]), '\0');
		return (0);
	}
	else
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (1);
	}
}
