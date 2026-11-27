/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 14:10:46 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/27 14:16:29 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int	main(void)
{
	void	*p;

	p = NULL;
	ft_printf("%c\n", 'M');
	ft_printf("%s\n", "Melvil");
	ft_printf("%p\n", p);
	ft_printf("%p\n", &p);
	ft_printf("%d\n", 14);
	ft_printf("%i\n", 03);
	ft_printf("%u\n", -1);
	ft_printf("%x\n", 348);
	ft_printf("%X\n", 348);
	ft_printf("%%\n");
	ft_printf("%\n");
}
