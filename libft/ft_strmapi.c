/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:42:07 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:46:08 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*output;

	if (!s)
		return (NULL);
	if (!f)
		return (ft_strdup(s));
	output = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (s[i])
	{
		output[i] = f(i, s[i]);
		i++;
	}
	output[i] = '\0';
	return (output);
}

// char	mel_upper(unsigned int i, char c)
// {
// 	(void) i;
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }

// int	main(void)
// {
// #include <stdio.h>
// 	printf("%s", ft_strmapi("hello world", mel_upper));
// }
