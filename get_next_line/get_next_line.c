/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 15:08:20 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/25 11:21:56 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*output;
	int			r;

	output = malloc(sizeof(char)*BUFFER_SIZE);
	r = read(fd, output, BUFFER_SIZE);
	printf("%s", output);
	return (output);
}

int	main(void)
{
	char	*output;
	int		fd;

	fd = open("fd.txt", O_RDONLY);
	output = get_next_line(fd);
	free(output);
}
