/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/19 12:17:12 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/19 23:52:11 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "push_swap.h"
#include "libft.h"

int	main(int argc, char *argv[])
{
	t_stacks	s;

	if (!parsestacks(&s, argc, argv))
		return (write(2, "Error\n", 6), 1);
	return (0);
}
