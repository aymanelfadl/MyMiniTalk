/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:20:35 by aelfadl           #+#    #+#             */
/*   Updated: 2024/12/11 13:20:46 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_calhex(void *n)
{
	unsigned long	num;
	char			c;
	int				count;

	count = 0;
	num = (unsigned long)n;
	if (num == 0)
		return (write(1, "(nil)", ft_strlen("(nil)")));
	if (num >= 16)
		count += ft_calhex((void *)(num / 16));
	if (num % 16 < 10)
		c = (num % 16) + '0';
	else
		c = (num % 16) - 10 + 'a';
	count += write(1, &c, 1);
	return (count);
}

int	ft_putadress(void *val)
{
	int	count;

	count = 0;
	if (!val)
		return (count = ft_calhex(val));
	else
		return (count = (write(1, "0x", ft_strlen("0x")) + ft_calhex(val)));
}
