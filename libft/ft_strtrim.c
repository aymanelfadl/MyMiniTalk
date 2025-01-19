/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:37:26 by aelfadl           #+#    #+#             */
/*   Updated: 2024/11/05 11:37:33 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_calstart(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	return (start);
}

static size_t	ft_calend(char const *s1, char const *set, size_t start)
{
	size_t	end;
	size_t	res;

	end = ft_strlen(s1);
	res = 0;
	while (end > start && ft_strchr(set, s1[end - 1]))
	{
		res++;
		end--;
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*ptr;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	start = ft_calstart (s1, set);
	end = ft_calend (s1, set, start);
	ptr = (char *) malloc ((ft_strlen(s1) - start - end + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (start < ft_strlen(s1) - end)
		ptr[i++] = s1[start++];
	ptr[i] = '\0';
	return (ptr);
}
