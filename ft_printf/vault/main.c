/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/22 00:55:33 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/22 17:06:55 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define W 30
#define STA "___________________________________________________________________\n"
#define SEP "|________________________________|________________________________|\n"
#define SPA "|                                |                                |\n"

static void pad(int n)
{
	while (n++ < W)
		ft_printf(" ");
}

#define TEST(...) \
	do { \
		int a; \
		int b; \
		ft_printf(SPA); \
		ft_printf("| "); \
		a = ft_printf(__VA_ARGS__); \
		pad(a); \
		ft_printf(" | "); \
		b = printf(__VA_ARGS__); \
		pad(b); \
		ft_printf(" |"); \
		if (a == b) \
			printf(GREEN " [OK]" RESET "\n"); \
		else \
			printf(RED " [KO]" RESET "\n"); \
		ft_printf(SEP); \
	} while (0)

int	main(void)
{
	int	c;
	char *n;

	c = 14;
	n = NULL;

	setvbuf(stdout, NULL, _IONBF, 0);
	ft_printf(STA);
	ft_printf(SPA);
	printf("| %-*s | %-*s |\n", W, "ft_printf", W, "printf");
	ft_printf(SEP);
	TEST("c : %c", 'M');
	TEST("s : %s", "Melvil");
	TEST("s : %s", n);
	TEST("p : %p", &c);
	TEST("d : %d", INT_MIN);
	TEST("d : %d", -1);
	TEST("u : %u", -1);
	TEST("x : %x", 348);
	TEST("x : %x", UINT_MAX);
	TEST("X : %X", 77);
	TEST("%c %s %d %x", 'a', "b", -5, 255);
	TEST("%%");
	TEST("Melvil%");
	return (0);
}
