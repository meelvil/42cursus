/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:33:51 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/10 10:26:54 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// int	main(void)
// {
// #include <stdio.h>
// 	t_list	*node;
// 	t_list	*one;
// 	t_list	*two;
// 	t_list	*three;
// 	t_list	*four;

// 	node = NULL;
// 	one = ft_lstnew((char *) "Hello World");
// 	two = ft_lstnew((char *) "Hi there");
// 	three = ft_lstnew((char *) "What's up");
// 	four = ft_lstnew((char *) "Good evening");
// 	ft_lstadd_front(&node, four);
// 	ft_lstadd_front(&node, three);
// 	ft_lstadd_front(&node, two);
// 	ft_lstadd_front(&node, one);
// 	printf("%s", (char *) ft_lstlast(node)->content);
// 	free(one);
// 	free(two);
// 	free(three);
// 	free(four);
// }
