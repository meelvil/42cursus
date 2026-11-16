/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_itoa.c                                         :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/06 15:20:38 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/12 09:10:03 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	long int	nb;
	int			i;

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

char	*ft_itoa(int n)
{
	int			i;
	long int	nb;
	char		*output;

	nb = n;
	i = count_digits(n);
	output = (char *) malloc(sizeof(char) * (i + 1));
	if (!output)
		return (NULL);
	output[i] = '\0';
	i--;
	if (nb < 0)
	{
		output[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		output[i] = '0';
	while (nb > 0)
	{
		output[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (output);
}

// int	main(void)
// {
// #include <stdio.h>
// 	printf("%s", ft_itoa(-2147483648));
// }
