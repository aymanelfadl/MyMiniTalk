/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:21:19 by aelfadl           #+#    #+#             */
/*   Updated: 2024/12/11 13:21:20 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(long n)
{
	int		count;
	int		isnega;
	char	c;

	isnega = 0;
	count = 0;
	if (n < 0)
	{
		n = -n;
		isnega = 1;
		write(1, "-", 1);
	}
	if (n / 10)
		count += ft_putnbr(n / 10);
	c = n % 10 + '0';
	count += write(1, &c, 1);
	return (count + isnega);
}
