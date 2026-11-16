/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:25:00 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/09 15:17:49 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*buf;

	buf = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		buf[i] = c;
		i++;
	}
	return (b);
}

// int main(void)
// {
//     #include <stdio.h>

//     char input[] = "12345 / Cette phrase commencera par 5 'a'";
//     ft_memset(input, 'a', 5);

//     printf("%s\n", input);
// }
