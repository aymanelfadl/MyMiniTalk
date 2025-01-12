/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:27:27 by aelfadl           #+#    #+#             */
/*   Updated: 2024/11/05 11:27:29 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hm(unsigned int nb)
{
	int	res;

	res = 1;
	while (nb / 10 > 0)
	{
		res++;
		nb /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*res;
	int				isnegga;
	int				t;

	nb = (unsigned int)n;
	isnegga = 0;
	if (n < 0)
	{
		nb = -(unsigned int)n;
		isnegga = 1;
	}
	t = ft_hm(nb) + isnegga;
	res = (char *)malloc((t + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[t] = '\0';
	while (t-- > isnegga)
	{
		res[t] = (nb % 10) + '0';
		nb /= 10;
	}
	if (isnegga)
		res[0] = '-';
	return (res);
}
