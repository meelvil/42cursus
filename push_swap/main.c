/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 12:17:12 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/20 09:24:53 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"
#include "libft.h"

int	main(int argc, char *argv[])
{
	t_stacks	s;
	int			i;

	i = 1;
	printf("%d\n", ft_atoi(argv[i]));
	if (!parsestacks(&s, argc, argv))
		return (write(2, "Error\n", 6), 1);
	i = argc - 1;
	while (i >= 1)
	{
		printf("%d\n", s.a[i]);
		i--;
	}
	return (0);
}
