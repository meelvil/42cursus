/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_printf.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/17 14:57:03 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/21 00:29:48 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] != '%')
		{
			count += ft_putchar(s[i]);
			i++;
		}
		else
		{
			i++;
			if (!s[i])
				break ;
			else
				count += ft_format(&args, s[i++]);
		}
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	ft_printf("%s\n%c\n%d", "Melvil", 'A', 14);
}
