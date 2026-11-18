/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:11:43 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/18 15:01:27 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(int n)
{
	long	nb;
	int		i;

	nb = n;
	i = 0;
	while (nb < 0)
	{
		nb *= -1;
		i++;
	}
	if (nb == 0)
		return (i + 1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	int		total;
	long	nb;

	nb = n;
	total = count_digits(nb);
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 0 && nb <= 9)
		ft_putchar(nb + '0');
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	return (total);
}

int	main(void)
{
#include <stdio.h>
	printf("\n%d", ft_putnbr(10000));
}
