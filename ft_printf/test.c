/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 10:05:51 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/18 10:39:54 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/****/
/*TEST PRINTF*/
/****/

int	main(void)
{
	printf("%u", 0);
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
