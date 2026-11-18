/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignednbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:28:58 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/18 16:13:36 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (i + 1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_putunsignednbr(unsigned int n)
{
	int	total;

	total = count_digits(n);
	if (n <= 9)
		ft_putchar(n + '0');
	if (n >= 10)
	{
		ft_putunsignednbr(n / 10);
		ft_putunsignednbr(n % 10);
	}
	return (total);
}

// int	main(void)
// {
// #include <stdio.h>
// 	printf("\n%d\n", ft_putunsignednbr(-1));
// 	printf("\n%d\n", ft_putunsignednbr(0));
// }
