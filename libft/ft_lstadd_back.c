/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:49:32 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/10 10:30:08 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

// int	main(void)
// {
// #include <stdio.h>
// 	t_list	*node;
// 	t_list	*one;
// 	t_list	*two;
// 	t_list	*three;
// 	t_list	*four;
// 	t_list	*five;

// 	node = NULL;
// 	one = ft_lstnew((char *) "Hello World");
// 	two = ft_lstnew((char *) "Hi there");
// 	three = ft_lstnew((char *) "What's up");
// 	four = ft_lstnew((char *) "Good evening");
// 	five = ft_lstnew((char *) "Have a good day");
// 	ft_lstadd_front(&node, four);
// 	ft_lstadd_front(&node, three);
// 	ft_lstadd_front(&node, two);
// 	ft_lstadd_front(&node, one);
// 	ft_lstadd_back(&node, five);
// 	printf("%s", (char *) ft_lstlast(node)->content);
// 	free(one);
// 	free(two);
// 	free(three);
// 	free(four);
// 	free(five);
// }
