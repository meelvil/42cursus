/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   atoicheck.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/03 11:53:56 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/20 15:23:58 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

int	atoicheck(char *str, int *out)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = sign * -1;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result * sign > 2147483647 || result * sign < -2147483648)
			return (0);
		i++;
	}
	*out = (int)(result * sign);
	return (1);
}

// int main(void)
// {
//     #include <stdio.h>

//     printf("%d", ft_atoi("  +123"));
// }
