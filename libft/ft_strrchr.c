/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_strrchr.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/03 14:35:40 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 10:54:12 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	character;

	str = (char *) s;
	character = (char) c;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == character)
			return (&str[i]);
		if (i == 0)
			break ;
		i--;
	}
	return (0);
}

// int	main(void)
// {
// #include <stdio.h>
// #include <string.h>
// 	char	*str = "Hello World";
// 	char	c = 'H';
// 	char	*result = ft_strrchr(str, c);
// 	char	*result_libc = strrchr(str, c);

// 	if (result)
// 		printf("Last '%c' found at position: %ld\n", c, (result + 1) - str);
// 	if (result_libc)
// 		printf("Last '%c' found at position (libc): %ld\n", c, (result_libc
// 			+1) - str);
// 	else
// 		printf("'%c' not found in the string.\n", c);
// 	return (0);
// }
