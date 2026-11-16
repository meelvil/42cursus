/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_isalnum.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/03 13:43:07 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 09:24:35 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

// int main(void)
// {
// 	#include <stdio.h>

// - returns 1
// 	printf("%d\n", ft_isdigit('1'));

// - returns 1
// 	printf("%d\n", ft_isdigit('M'));

// - returns 0
// 	printf("%d\n", ft_isdigit('-'));
// }
