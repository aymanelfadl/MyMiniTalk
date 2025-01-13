/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:21:03 by aelfadl           #+#    #+#             */
/*   Updated: 2024/12/11 13:21:06 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexa(long n)
{
	unsigned int	num;
	char			c;
	int				count;

	count = 0;
	num = (unsigned int)n;
	if (num == 0)
		return (write(1, "0", 1));
	if (num >= 16)
		count += ft_puthexa(num / 16);
	if (num % 16 < 10)
		c = (num % 16) + '0';
	else
		c = (num % 16) - 10 + 'a';
	count += write(1, &c, 1);
	return (count);
}
