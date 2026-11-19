/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 12:17:12 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/19 12:38:41 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"
#include "libft.h"

int	main(int argc, char *argv[])
{
	int	i;
	int	*tab;
	int	*subtab;

	if (argc < 4)
		return (0);
	tab = malloc(sizeof(int) * (argc - 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < argc - 1)
	{
		tab[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	subtab = sorttab(tab);
	i = 0;
	while (subtab && i < 3)
		printf("%d\n", subtab[i++]);
	free(subtab);
	free(tab);
	return (0);
}
