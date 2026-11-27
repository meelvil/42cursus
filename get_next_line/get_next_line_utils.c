/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_utils.c                             :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/26 10:54:27 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/26 12:04:00 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*substring;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	if (len > slen - start)
		len = slen - start;
	substring = malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		s2 = "";
	joined = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!joined)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1 && s1[i])
		joined[j++] = s1[i++];
	i = 0;
	free(s1);
	while (s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	return (joined);
}
