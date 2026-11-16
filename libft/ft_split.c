/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 13:42:50 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/06 15:12:47 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*wordsep(char const *s, size_t *i, char c)
{
	char	*word;
	size_t	start;
	size_t	n;

	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	n = *i - start;
	word = malloc(sizeof(char) * (n + 1));
	if (!word)
		return (NULL);
	n = 0;
	while (start + n < *i)
	{
		word[n] = s[start + n];
		n++;
	}
	word[n] = '\0';
	return (word);
}

void	freesplit(char **splitted, int j)
{
	while (j >= 0)
	{
		free(splitted[j]);
		j--;
	}
	free(splitted);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**splitted;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	splitted = malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!splitted)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			splitted[j] = wordsep(s, &i, c);
			if (!splitted[j])
				return (freesplit(splitted, j - 1), NULL);
			j++;
		}
		else
			i++;
	}
	splitted[j] = 0;
	return (splitted);
}

// int	main(int argc, char *argv[])
// {
// #include <stdio.h>
// 	char	**splitted;
// 	int		i;

// 	if (argc < 2)
// 	{
// 		return (0);
// 	}
// 	i = 0;
// 	printf("%s\n\n", argv[1]);
// 	splitted = ft_split(argv[1], ' ');
// 	while (splitted[i])
// 	{
// 		printf("%s\n", splitted[i]);
// 		free(splitted[i]);
// 		i++;
// 	}
// 	free(splitted[i]);
// 	return (0);
// }
