/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:09:36 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:49:11 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// void	del(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// #include <stdio.h>
// 	t_list	*node;
// 	t_list	*one;
// 	t_list	*two;
// 	t_list	*three;

// 	node = NULL;
// 	one = ft_lstnew((char *) ft_strdup("Hello World"));
// 	two = ft_lstnew((char *) ft_strdup("Hi there"));
// 	three = ft_lstnew((char *) ft_strdup("What's up"));
// 	ft_lstadd_back(&node, one);
// 	ft_lstadd_back(&node, two);
// 	ft_lstadd_back(&node, three);
// 	printf("Size before deletion : %d\n", ft_lstsize(node));
// 	ft_lstdelone(three, del);
// 	two->next = NULL;
// 	printf("Size after deletion : %d\n", ft_lstsize(node));
// 	free(one);
// 	free(two);
// }
