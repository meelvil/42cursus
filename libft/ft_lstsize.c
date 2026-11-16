/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 09:02:06 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/10 09:32:39 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_lstsize(t_list *lst)
{
	unsigned int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
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
// 	printf("%d", ft_lstsize(node));
// 	free(one);
// 	free(two);
// 	free(three);
// 	free(four);
// }
