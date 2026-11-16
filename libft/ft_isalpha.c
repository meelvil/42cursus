/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_isalpha.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/02 11:55:27 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 09:24:46 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// int main(void)
// {
// 	#include <stdio.h>

// - returns 1
// 	printf("%d\n", ft_isdigit('M'));

// - returns 0
// 	printf("%d\n", ft_isdigit('1'));
// }
