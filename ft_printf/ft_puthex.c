/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_puthex.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/21 13:18:37 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/22 01:22:16 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lowerhex(unsigned int n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n > 15)
		return (ft_lowerhex(n / 16) + ft_putchar(hex[n % 16]));
	return (ft_putchar(hex[n]));
}

int	ft_upperhex(unsigned int n)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (n > 15)
		return (ft_upperhex(n / 16) + ft_putchar(hex[n % 16]));
	return (ft_putchar(hex[n]));
}

int	ft_longhex(unsigned long n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n > 15)
		return (ft_longhex(n / 16) + ft_putchar(hex[n % 16]));
	return (ft_putchar(hex[n]));
}
