/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_isprint.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 09:47:21 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 09:27:03 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// int	main(void)
// {
// #include <stdio.h>
// 	// - returns 1
// 	printf("%d\n", ft_isprint('M'));
// 	// - returns 0
// 	printf("%d\n", ft_isprint('\n'));
// }
