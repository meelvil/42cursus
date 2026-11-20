/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   test.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/16 10:05:51 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/20 17:36:55 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

/****/
/*TEST PRINTF*/
/****/

int	main(void)
{
	printf("H");
}

/****/
/*TEST PRINT STRING FROM ARGUMENT*/
/****/

// char *printstring(int count, ...)
// {
// 	va_list args;
// 	char *string;

// 	va_start(args, count);
// 	string = va_arg(args, char *);
// 	va_end(args);
// 	return (string);
// }

// // int main(void)
// // {
// // 	printf("%s", printstring(5, "Melvil", 0));
// // }

/****/
/*TEST RETURN SUM FROM ARGUMENTS*/
/****/

// int	sumargs(int count, ...)
// {
// 	va_list	args;
// 	int		total;

// 	va_start(args, count);
// 	total = 0;
// 	while (count--)
// 	{
// 		total += va_arg(args, int);
// 	}
// 	va_end(args);
// 	return (total);
// }

// int	main(void)
// {
// 	printf("%d", sumargs(3, 6, 4, 0));
// }

/****/
/*TEST RETURN SUM FROM ARGUMENTS*/
/****/

// int	ft_add_two(va_list *args)
// {
// 	int	a;
// 	int	b;

// 	a = va_arg(*args, int);
// 	b = va_arg(*args, int);
// 	return (a + b);
// }

// int	ft_sum_pairs(int pairs, ...)
// {
// 	va_list	args;
// 	int		total;

// 	va_start(args, pairs);
// 	total = 0;
// 	while (pairs--)
// 		total += ft_add_two(&args);
// 	va_end(args);
// 	return (total);
// }

// int	main(void)
// {
// 	printf("%d", ft_sum_pairs(2, 1, 4, 5, 10));
// }
