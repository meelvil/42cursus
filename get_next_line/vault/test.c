/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 10:52:23 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/25 12:37:21 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	compte_local(void)
{
	int	local;

	local = 0;
	local++;
	printf("%d\n", local);
}

void	compte_static(void)
{
	static char	stat = '`';

	if (stat != 'c')
		stat++;
	else
		stat = 'a';
	printf("%c\n", stat);
}

int	ft_strlen(char *ext)
{
	int	i;

	i = 0;
	while (ext[i])
		i++;
	return (i);
}

char	*malloc_static(char *ext)
{
	static char	*str = NULL;
	int			i;

	i = 0;
	free(str);
	str = malloc(sizeof(char) * (ft_strlen(ext) + 1));
	if (!str)
		return (NULL);
	while (ext[i])
	{
		str[i] = ext[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	main(void)
{
	int	repeat;

	repeat = 0;
	printf("Local :\n");
	while (repeat < 3)
	{
		compte_local();
		repeat++;
	}
	repeat = 0;
	printf("\nStatic :\n");
	while (repeat < 6)
	{
		compte_static();
		repeat++;
	}
	repeat = 0;
	printf("\nMalloc Static :\n");
	// while (repeat < 3)
	// {
	// 	printf("%s\n", malloc_static("a"));
	// 	repeat++;
	// }
	char	*str = malloc_static("a");

	printf("%s\n", str);
	str = malloc_static("bb");
	printf("%s\n", str);
	str = malloc_static("ccc");
	printf("%s\n", str);
	free(str);
}
