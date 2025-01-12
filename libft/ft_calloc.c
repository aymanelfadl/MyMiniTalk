/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:24:59 by aelfadl           #+#    #+#             */
/*   Updated: 2024/11/06 14:36:24 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return ((void *)ptr);
}
