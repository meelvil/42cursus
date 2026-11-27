/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/23 15:08:20 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/27 09:17:14 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

static char	*free_all(char *a, char *b)
{
	free(a);
	free(b);
	return (NULL);
}

static char	*accumulate_read(int fd, char *saved)
{
	char	*local_read;
	int		r;

	r = 1;
	local_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!local_read)
		return (free_all(saved, NULL));
	while (!ft_strchr(saved, '\n') && r > 0)
	{
		r = read(fd, local_read, BUFFER_SIZE);
		if (r == -1)
			return (free_all(local_read, saved));
		local_read[r] = '\0';
		saved = ft_strjoin(saved, local_read);
		if (!saved)
			return (free_all(local_read, NULL));
	}
	free(local_read);
	return (saved);
}

static char	*extract_line(char *saved)
{
	int	i;

	if (!saved || saved[0] == '\0')
		return (NULL);
	i = 0;
	while (saved[i] != '\0' && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	return (ft_substr(saved, 0, i));
}

static char	*keep_rest(char *saved)
{
	int		i;
	char	*rest;

	if (!saved || saved[0] == '\0')
		return (NULL);
	i = 0;
	while (saved[i] != '\0' && saved[i] != '\n')
		i++;
	if (saved[i] == '\n')
		i++;
	if (saved[i] == '\0')
		return (free_all(saved, NULL));
	rest = ft_substr(saved, i, ft_strlen(saved) - i);
	free(saved);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_str = accumulate_read(fd, static_str);
	if (!static_str)
		return (NULL);
	line = extract_line(static_str);
	if (!line)
	{
		free(static_str);
		static_str = NULL;
		return (NULL);
	}
	static_str = keep_rest(static_str);
	return (line);
}

// int	main(void)
// {
// 	char	*output;
// 	int		fd;
// 	int		i;

// 	fd = open("./fd_tests/12_melange.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	i = 1;
// 	while (i <= 4)
// 	{
// 		output = get_next_line(fd);
// 		if (!output)
// 			break ;
// 		printf("appel %d : %s\n", i, output);
// 		free(output);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
