/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_putstr.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/16 14:47:42 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/20 17:21:54 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	if (s)
		return (write(1, s, ft_strlen(s)));
	return (0);
}

/*int main(void)
{
// #include <stdio.h>
printf("\n%d", ft_putstr("Melvil"));
}*/
