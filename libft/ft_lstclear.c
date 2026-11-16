/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:31:05 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/10 10:57:18 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
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
// 	printf("Size before clear: %u elements\n", ft_lstsize(node));
// 	ft_lstclear(&node, del);
// 	printf("Size after clear: %u elements\n", ft_lstsize(node));
// }
