/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_printf.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/17 14:57:03 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/25 10:15:54 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		r;

	i = -1;
	count = 0;
	va_start(args, s);
	while (s[++i])
	{
		if (s[i] != '%')
			r = ft_putchar(s[i]);
		else if (s[++i])
			r = ft_format(&args, s[i]);
		else
			break ;
		if (r == -1)
		{
			va_end(args);
			return (-1);
		}
		count += r;
	}
	va_end(args);
	return (count);
}
