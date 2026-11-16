/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_memchr.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 14:04:44 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/12 09:11:15 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *) str;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char) c)
			return (&p[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
//     #include <stdio.h>
//     #include <string.h>

//     char *str = "Hello World";
//     char c = 'o';
//     char *result = ft_memchr(str, c, 5);
//     char *result_libc = memchr(str, c, 5);

//     if (result)
//         printf("'%c' found at position: %ld\n", c, (result + 1) - str);
//     if (result_libc)
//         printf("'%c' found at position (libc): %ld\n", c, (result_libc + 1)
// 	- str);
//     else
//         printf("'%c' not found in the string.\n", c);

//     return (0);
// }
