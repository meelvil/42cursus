/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_calloc.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 15:05:34 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/12 09:07:39 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*toalloc;

	if (count && size > (size_t) - 1 / count)
		return (NULL);
	toalloc = malloc(count * size);
	if (!toalloc)
		return (NULL);
	ft_bzero(toalloc, count * size);
	return (toalloc);
}

// int main(void)
// {
//     #include <stdio.h>

//     char *wafpaf;

//     wafpaf = ft_calloc(7, sizeof(char));
//     printf("%lu\n", strlen(wafpaf));
//     wafpaf = "Melvilllll";
//     printf("%lu\n", strlen(wafpaf));
//     printf("%s\n", wafpaf);
// }
