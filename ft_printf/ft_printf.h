/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 09:54:51 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/27 10:37:04 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *s, ...);
int	ft_format(va_list *args, char c);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putunsignednbr(unsigned int n);
int	ft_printadress(void *p);
int	ft_lowerhex(unsigned int n);
int	ft_upperhex(unsigned int n);
int	ft_longhex(unsigned long n);

#endif
