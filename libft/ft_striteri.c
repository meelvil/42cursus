/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:48:06 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:28:17 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	mel_upper(unsigned int i, char *s)
// {
// 	(void) i;
// 	if (*s >= 'a' && *s <= 'z')
// 		*s = *s - 32;
// }

// int	main(void)
// {
// #include <stdio.h>
// 	char	output[] = "Hello World";

// 	ft_striteri(output, mel_upper);
// 	printf("%s", output);
// }
