/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_printf.h                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mbou-ani <mbou-ani@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/16 09:54:51 by mbou-ani         #+#    #+#              */
/*   Updated: 2026/11/22 01:16:33 by mbou-ani        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	ft_printf(const char *s, ...);
int	ft_strlen(char *s);
int	ft_format(va_list *args, char c);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putunsignednbr(unsigned int n);
int	ft_printadress(void *p);
int	ft_lowerhex(unsigned int n);
int	ft_upperhex(unsigned int n);
int	ft_longhex(unsigned long n);
