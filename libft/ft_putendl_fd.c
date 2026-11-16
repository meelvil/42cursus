/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 12:58:49 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:22:52 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
		ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// int	main(void)
// {
// #include <fcntl.h>
// 	int		fd = open("txt/ft_putendl_fd.txt", O_WRONLY);
// 	char	out[] = "Hello";
// 	char	put[] = "World";

// 	ft_putendl_fd(out, fd);
// 	ft_putendl_fd(put, fd);
// }
