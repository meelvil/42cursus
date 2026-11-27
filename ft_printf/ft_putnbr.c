/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:11:43 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/27 10:37:08 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long	nb;
	int		sign;
	int		numbers;

	sign = 0;
	nb = n;
	if (n < 0)
	{
		sign = ft_putchar('-');
		if (sign < 0)
			return (-1);
		nb = -nb;
	}
	numbers = ft_putunsignednbr((unsigned int) nb);
	if (numbers < 0)
		return (-1);
	return (sign + numbers);
}
