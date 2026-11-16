/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:52:50 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:04:16 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*output;

	if (!s1)
		return (NULL);
	output = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

// int	main(void)
// {
//     #include <stdio.h>

// 	printf("%s\n", ft_strdup("Melvil"));
// }
