/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:57:03 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/18 10:35:25 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	if (ispercent((char *) s))
		return (1);
	return (0);
}

int	main(void)
{
	printf("%d", ft_printf("Hey"));
}
