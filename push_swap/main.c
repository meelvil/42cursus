/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 12:17:12 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/23 11:03:38 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_stacks	s;
	int			i;

	i = 1;
	if (argc < 2)
		return (0);
	if (!parsestacks(&s, argc, argv))
		return (write(2, "Error\n", 6), 1);
	i = 0;
	while (i < s.size_a)
	{
		printf("%d\n", s.a[i]);
		i++;
	}
	return (0);
}
