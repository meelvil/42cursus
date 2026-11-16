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
	char	*main;
	char	*tofind;

	main = (char *) big;
	tofind = (char *) little;
	if (tofind[0] == '\0')
		return (main);
	i = 0;
	while (main[i] && i < len)
	{
		j = 0;
		while (main[i + j] && j + i < len && main[i + j] == tofind[j])
		{
			if (tofind[j + 1] == '\0')
				return (&main[i]);
			j++;
		}
		i++;
	}
	return (0);
}

// int main(void)
// {
//     #include <stdio.h>

//     char *output;

//     output = ft_strnstr("Hello World", "World", 15);

//     if (output)
//         printf("%s\n", output);
//     else
//         printf("0\n");
// }
