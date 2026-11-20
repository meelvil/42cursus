/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parsestacks.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 12:25:24 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/20 09:27:16 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "push_swap.h"

int	*parsestacks(t_stacks *s, int argc, char *argv[])
{
	int	index;
	int	parse;

	s->a = malloc(sizeof(int) * (argc - 1));
	s->b = malloc(sizeof(int) * (argc - 1));
	s->size_a = argc - 1;
	s->size_b = argc - 1;
	index = argc - 1;
	while (index >= 1)
	{
		s->a[parse] = ft_atoi(argv[index]);
		index--;
		parse++;
	}
	return (s->a);
}
