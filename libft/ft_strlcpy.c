/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 11:49:19 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:00:03 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	if (!dst || !src)
		return (ft_strlen(src));
	i = 0;
	srclen = 0;
	while (src[srclen])
		srclen++;
	if (size == 0)
		return (srclen);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

// int    main(void)
// {
//     #include <unistd.h>

//     char    test[50] = "Hello ";
//     char    src[50] = "Mister";
//     char    result;

//     result = ft_strlcpy(test, src, 2) + '0';
//     write(1, &result, 1);
//     write(1, "\n", 1);
//     write(1, test, 50);
// }
