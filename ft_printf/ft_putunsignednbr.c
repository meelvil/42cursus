/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putunsignednbr.c                               :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/18 14:28:58 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/22 16:20:59 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsignednbr(unsigned int n)
{
	int	x;
	int	y;

	if (n >= 10)
	{
		x = ft_putunsignednbr(n / 10);
		if (x == -1)
			return (-1);
		y = ft_putunsignednbr(n % 10);
		if (y == -1)
			return (-1);
		return (x + y);
	}
	return (ft_putchar(n + '0'));
}
