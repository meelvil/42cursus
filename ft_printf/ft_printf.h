/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_printf.h                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/16 09:54:51 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/18 15:50:47 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putunsignednbr(unsigned int n);
int	ft_percent(char *s);
int	ft_strlen(char *s);
int	ft_printf(const char *s, ...);
