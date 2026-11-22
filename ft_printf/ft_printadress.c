/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_printadress.c                                  :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/22 01:08:07 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/22 16:27:38 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printadress(void *p)
{
	int	x;
	int	y;

	if (!p)
		return (ft_putstr("(nil)"));
	x = ft_putstr("0x");
	if (x == -1)
		return (-1);
	y = ft_longhex((unsigned long) p);
	if (y == -1)
		return (-1);
	return (x + y);
}
