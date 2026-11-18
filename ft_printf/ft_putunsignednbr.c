/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignednbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:28:58 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/18 15:44:50 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(int n)
{
	unsigned int	nb;
	int				i;

	nb = (unsigned int) n;
	i = 0;
	if (nb == 0)
		return (i + 1);
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ft_putunsignednbr(int n)
{
	int				total;
	unsigned int	nb;

	nb = (unsigned int) n;
	total = count_digits(nb);
	if (nb >= 0 && nb <= 9)
		ft_putchar(nb + '0');
	if (nb >= 10)
	{
		ft_putunsignednbr(nb / 10);
		ft_putunsignednbr(nb % 10);
	}
	return (total);
}

int	main(void)
{
#include <stdio.h>
	printf("\n%d", ft_putunsignednbr(1));
}
