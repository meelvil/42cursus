/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 14:57:03 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/17 15:08:58 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ispercent(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
			return (1);
		i++;
	}
	return (0);
}

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
