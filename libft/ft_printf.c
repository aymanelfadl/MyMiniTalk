/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:20:05 by aelfadl           #+#    #+#             */
/*   Updated: 2024/12/11 14:46:20 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wechkine(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (!(ft_strchr("csiupdxX%", str[i])))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_printer(const char *c, va_list args, const char *str)
{
	if (*c == 'd' || *c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (*c == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	else if (*c == 'x')
		return (ft_puthexa(va_arg(args, int)));
	else if (*c == 'X')
		return (ft_puthexam(va_arg(args, int)));
	else if (*c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (*c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (*c == 'p')
		return (ft_putadress(va_arg(args, char *)));
	else if (*c == '%')
		return (write(1, "%", 1));
	else if (*c == '\0' && !ft_wechkine(str))
		return (-1);
	else if (*c == '\0' && ft_wechkine(str))
		return (write(1, c - 1, 1));
	return (write(1, c - 1, 1) + write(1, c, 1));
}

int	ft_lop(const char *str, int *i, va_list args)
{
	int	ret;
	int	count;

	*i = 0;
	ret = 0;
	count = 0;
	while (str[*i])
	{
		if (str[*i] == '%')
		{
			(*i)++;
			ret = ft_printer(str + (*i), args, str);
			if (ret == -1)
				return (-1);
			count += ret;
			if (!str[*i])
				break ;
		}
		else
			count += write(1, &str[*i], 1);
		(*i)++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	count = 0;
	va_start(args, str);
	if (!str)
		return (0);
	count = ft_lop(str, &i, args);
	va_end(args);
	return (count);
}
