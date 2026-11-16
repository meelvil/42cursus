/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_bzero.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 11:37:25 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/06 09:31:46 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

// int main(void)
// {
//     #include <stdio.h>

//     char input[] = "12345 / Cette phrase commencera par 5 '0'";
//     ft_bzero(input, 5);

//     printf("%s\n", input);
// }
