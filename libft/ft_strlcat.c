/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 11:39:09 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:02:49 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;
	size_t	src_len;

	if (!dst)
		return (ft_strlen(src));
	if (!src)
		return (ft_strlen(dst));
	i = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (src_len + size);
	while (src[i] && (dest_len + i) < (size - 1))
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// int	main(void)
// {
// #include <stdio.h>
// #include <bsd/string.h>

// 	{
// 		char dest[15] = "Hey";
// 		char *src = "oMelvil";

// 		printf("Source : %s Destination : %s\n\n", src, dest);
// 		printf("Longueur totale visee (dest+src) : %d\n", ft_strlcat(dest, src,
// 				2));
// 		printf("Destination apres concatenation : %s\n", dest);
// 	}

// 	printf("--------------------\n");

// 	{
// 		char dest[15] = "Hey";
// 		char *src = "oMelvil";

// 		printf("Source : %s Destination : %s\n\n", src, dest);
// 		printf("Longueur totale visee (dest+src) : %zu\n", strlcat(dest, src,
// 				2));
// 		printf("Destination apres concatenation : %s\n", dest);
// 	}
// }
