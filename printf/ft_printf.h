/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:19:49 by aelfadl           #+#    #+#             */
/*   Updated: 2024/12/11 13:25:33 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

int		ft_puthexa(long n);
int		ft_puthexam(long n);
int		ft_putadress(void *val);
int		ft_putnbr(long n);
int		ft_strlen(char *s);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_printf(const char *str, ...);
char	*ft_strchr(const char *s, int c);

#endif
