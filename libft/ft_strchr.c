/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 14:08:07 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/16 13:34:53 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		count;
	char	character;

	character = (char) c;
	count = ft_strlen(s);
	i = 0;
	while (i <= count)
	{
		if (s[i] == character)
			return ((char *) & s[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
//     #include <stdio.h>
//     #include <string.h>

//     char *str = "Hello World";
//     char c = '\0';
//     char *result = ft_strchr(str, c);
//     char *result_libc = strchr(str, c);

//     if (result)
//         printf("'%c' found at position: %ld\n", c, (result + 1) - str);
//     if (result_libc)
//         printf("'%c' found at position (libc): %ld\n", c, (result_libc + 1)
// - str);
//     else
//         printf("'%c' not found in the string.\n", c);

//     return (0);
// }
