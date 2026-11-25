/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parsestacks.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 12:25:24 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/23 10:54:52 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int	*parsestacks(t_stacks *s, int argc, char *argv[])
{
	int	index;

	s->a = malloc(sizeof(int) * (argc - 1));
	if (!s->a)
		return (NULL);
	s->b = malloc(sizeof(int) * (argc - 1));
	if (!s->b)
	{
		free(s->a);
		return (NULL);
	}
	s->size_a = argc - 1;
	s->size_b = 0;
	index = 1;
	while (index < argc)
	{
		if (!atoicheck(argv[index], &s->a[index - 1]))
			return (NULL);
		index++;
	}
	return (s->a);
}
