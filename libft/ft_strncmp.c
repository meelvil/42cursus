/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_strncmp.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/03 11:44:18 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 09:52:19 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				value;
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	value = 0;
	while (i < n && (str1[i] || str2[i]))
	{
		value = str1[i] - str2[i];
		if (value != 0)
			return (value);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	#include <stdio.h>

// 	printf("%d", ft_strncmp("Melvil", "Melviil", 5));
// }
