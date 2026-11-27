/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 13:18:37 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/27 10:37:06 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lowerhex(unsigned int n)
{
	char	*hex;
	int		x;
	int		y;

	hex = "0123456789abcdef";
	if (n > 15)
	{
		x = ft_lowerhex(n / 16);
		if (x == -1)
			return (-1);
		y = ft_putchar(hex[n % 16]);
		if (y == -1)
			return (-1);
		return (x + y);
	}
	return (ft_putchar(hex[n]));
}

int	ft_upperhex(unsigned int n)
{
	char	*hex;
	int		x;
	int		y;

	hex = "0123456789ABCDEF";
	if (n > 15)
	{
		x = ft_upperhex(n / 16);
		if (x == -1)
			return (-1);
		y = ft_putchar(hex[n % 16]);
		if (y == -1)
			return (-1);
		return (x + y);
	}
	return (ft_putchar(hex[n]));
}

int	ft_longhex(unsigned long n)
{
	char	*hex;
	int		x;
	int		y;

	hex = "0123456789abcdef";
	if (n > 15)
	{
		x = ft_longhex(n / 16);
		if (x == -1)
			return (-1);
		y = ft_putchar(hex[n % 16]);
		if (y == -1)
			return (-1);
		return (x + y);
	}
	return (ft_putchar(hex[n]));
}
