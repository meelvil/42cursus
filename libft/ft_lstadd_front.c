/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 16:04:21 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 11:21:53 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// #include <stdio.h>
// 	t_list	*lst;
// 	t_list	*new;

// 	lst = NULL;
// 	new = ft_lstnew((void *) "Hello World");
// 	ft_lstadd_front(&lst, new);
// 	printf("%s", (char *)(lst->content));
//  free(new);
// }
