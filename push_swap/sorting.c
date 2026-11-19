/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   sorting.c                                         :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 12:25:24 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/19 12:39:36 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*sorttab(int *tab, int argc)
{
	int	i;
	int	*subtab;

	subtab = malloc(sizeof(int) * (argc - 1));
	if (!subtab)
		return (NULL);
	i = 0;
	while (i < 3)
	{
		subtab[i] = tab[i];
		i++;
	}
	return (subtab);
}
