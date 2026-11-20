/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_format.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/20 18:47:05 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/21 00:37:53 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(va_list *args, char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	if (c == 'p')
		return ((ft_putstr("To DO")));
	if (c == 'd')
		return (ft_putnbr(va_arg(*args, int)));
	if (c == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	if (c == 'u')
		return (ft_putunsignednbr(va_arg(*args, unsigned int)));
	if (c == 'x')
		return (ft_putunsignednbr(va_arg(*args, unsigned int)));
	if (c == 'X')
		return (ft_putunsignednbr(va_arg(*args, unsigned int)));
	if (c == '%')
		return (((ft_putchar('%'))));
}
