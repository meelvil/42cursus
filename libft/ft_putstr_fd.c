/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 12:05:18 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:23:33 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

// int	main(void)
// {
// #include <fcntl.h>
// 	int		fd = open("txt/ft_putstr_fd.txt", O_WRONLY);
// 	char	output[] = "Hello World";

// 	ft_putstr_fd(output, fd);
// }
