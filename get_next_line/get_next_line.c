/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/23 15:08:20 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/23 15:30:57 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	char	*output;
	int		r;

	output = malloc(sizeof(char *) * 7);
	r = read(fd, output, 7);
	return (output);
}

int	main(void)
{
	char	*output;
	int		fd = open("fd.txt", O_RDONLY);

	output = get_next_line(fd);
	printf("%s", output);
}
