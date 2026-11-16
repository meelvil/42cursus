/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 11:00:49 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/10 11:36:01 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void	mel_lstupper(void *content)
// {
// 	char	*s;

// 	s = (char *) content;
// 	while (*s)
// 	{
// 		if (*s >= 'a' && *s <= 'z')
// 			*s = *s - 32;
// 		s++;
// 	}
// }

// int	main(void)
// {
// #include <stdio.h>
// 	t_list	*node;

// 	node = ft_lstnew((char *) ft_strdup("hello world"));
// 	printf("Before function : %s\n", (char *)(node->content));
// 	ft_lstiter(node, mel_lstupper);
// 	printf("After function : %s\n", (char *)(node->content));
// }
