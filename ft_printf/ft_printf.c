/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:57:03 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/18 14:50:42 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;

	va_start(args, s);
	if (ispercent((char *) s))
		return (1);
	return (0);
}

// int	main(void)
// {
// #include <stdio.h>
// 	printf("%d", ft_printf("Hey"));
// }
