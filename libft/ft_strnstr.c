/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_strnstr.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 09:55:46 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 11:02:48 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*big_ptr;
	char	*lit_ptr;

	big_ptr = (char *) big;
	lit_ptr = (char *) little;
	if (lit_ptr[0] == '\0')
		return (big_ptr);
	i = 0;
	while (big_ptr[i] && i < len)
	{
		j = 0;
		while (big_ptr[i + j] && j + i < len && big_ptr[i + j] == lit_ptr[j])
		{
			if (lit_ptr[j + 1] == '\0')
				return (&big_ptr[i]);
			j++;
		}
		i++;
	}
	return (0);
}

// int big_ptr(void)
// {
//     #include <stdio.h>

//     char *output;

//     output = ft_strnstr("Hello World", "World", 15);

//     if (output)
//         printf("%s\n", output);
//     else
//         printf("0\n");
// }
