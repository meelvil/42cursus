/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 10:48:15 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/27 14:09:40 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_all(char *a, char *b)
{
	free(a);
	free(b);
	return (NULL);
}

static char	*fill_read(int fd, char *stat_s)
{
	char	*local_s;
	int		r;

	r = 1;
	local_s = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!local_s)
		return (free_all(stat_s, NULL));
	while (!ft_strchr(stat_s, '\n') && r > 0)
	{
		r = read(fd, local_s, BUFFER_SIZE);
		if (r == -1)
			return (free_all(local_s, stat_s));
		local_s[r] = '\0';
		stat_s = ft_strjoin(stat_s, local_s);
		if (!stat_s)
			return (free_all(local_s, NULL));
	}
	free(local_s);
	return (stat_s);
}

static char	*extract_lines(char *stat_s)
{
	int	i;

	if (!stat_s || stat_s[0] == '\0')
		return (NULL);
	i = 0;
	while (stat_s[i] != '\0' && stat_s[i] != '\n')
		i++;
	if (stat_s[i] == '\n')
		i++;
	return (ft_substr(stat_s, 0, i));
}

static char	*keep_rest(char *stat_s)
{
	char	*rest;
	int		i;

	if (!stat_s || stat_s[0] == '\0')
		return (NULL);
	i = 0;
	while (stat_s[i] != '\0' && stat_s[i] != '\n')
		i++;
	if (stat_s[i] == '\n')
		i++;
	if (stat_s[i] == '\0')
		return (free_all(stat_s, NULL));
	rest = ft_substr(stat_s, i, ft_strlen(stat_s) - i);
	free(stat_s);
	return (rest);
}
// ----

char	*get_next_line(int fd)
{
	static char	*static_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_str = fill_read(fd, static_str);
	if (!static_str)
		return (NULL);
	line = extract_lines(static_str);
	if (!line)
	{
		free(static_str);
		static_str = NULL;
		return (NULL);
	}
	static_str = keep_rest(static_str);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(int argc, char *argv[])
// {
// 	char	*output;
// 	int		fd;
// 	int		i;

// 	if (argc < 2)
// 		return (0);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	i = 1;
// 	while (1)
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
