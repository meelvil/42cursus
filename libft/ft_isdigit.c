/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_isdigit.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/02 11:34:02 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 09:33:09 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int main(void)
// {
// 	#include <stdio.h>

// - returns 1
// 	printf("%d\n", ft_isdigit('1'));

// - returns 0
// 	printf("%d\n", ft_isdigit('M'));
// }
