/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_memcmp.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 14:08:27 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 09:35:00 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] - p2[i] != 0)
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	#include <stdio.h>

// 	printf("%d", ft_memcmp("Melvil", "Meelvil", 5));
// }
