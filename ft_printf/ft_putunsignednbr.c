/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putunsignednbr.c                               :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/18 14:28:58 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/21 00:10:51 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_putunsignednbr(unsigned int n)
{
	if (n >= 10)
	{
		return (ft_putunsignednbr(n / 10) + ft_putunsignednbr(n % 10));
	}
	return (ft_putchar(n + '0'));
}

// int	main(void)
// {
// 	// #include <stdio.h>
// 	printf("\n%d\n", ft_putunsignednbr(-1));
// 	printf("\n%d\n", ft_putunsignednbr(0));
// }
