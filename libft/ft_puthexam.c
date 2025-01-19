/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:20:20 by aelfadl           #+#    #+#             */
/*   Updated: 2024/12/11 13:24:43 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexam(long n)
{
	unsigned int	num;
	char			c;
	int				count;

	num = (unsigned int)n;
	count = 0;
	if (num == 0)
		return (write(1, "0", 1));
	if (num >= 16)
		count += ft_puthexam(num / 16);
	if (num % 16 < 10)
		c = (num % 16) + '0';
	else
		c = (num % 16) - 10 + 'A';
	count += write(1, &c, 1);
	return (count);
}
