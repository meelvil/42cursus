/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbou-ani <mbou-ani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 11:41:32 by mbou-ani          #+#    #+#             */
/*   Updated: 2026/11/12 12:05:47 by mbou-ani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*newnode;
	void	*content;

	if (!lst)
		return (NULL);
	nlst = NULL;
	while (lst)
	{
		if (f)
			content = f(lst->content);
		else
			content = lst->content;
		newnode = ft_lstnew(content);
		if (!newnode)
		{
			del(content);
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		ft_lstadd_back(&nlst, newnode);
		lst = lst->next;
	}
	return (nlst);
}

// void	del(void *content)
// {
// 	free(content);
// }
// void	*mel_lstupper(void *content)
// {
// 	char	*copy;
// 	char	*s;
// 	copy = ft_strdup((char *) content);
// 	if (!copy)
// 		return (NULL);
// 	s = copy;
// 	while (*s)
// 	{
// 		if (*s >= 'a' && *s <= 'z')
// 			*s = *s - 32;
// 		s++;
// 	}
// 	return ((void *) copy);
// }
// int	main(void)
// {
// #include <stdio.h>
// 	t_list	*lst;
// 	t_list	*mapped;
// 	t_list	*tmp;
// 	lst = NULL;
// 	ft_lstadd_back(&lst, ft_lstnew((void *) "hello"));
// 	ft_lstadd_back(&lst, ft_lstnew((void *) "world"));
// 	ft_lstadd_back(&lst, ft_lstnew((void *) "42"));
// 	mapped = ft_lstmap(lst, mel_lstupper, del);
// 	tmp = mapped;
// 	while (tmp)
// 	{
// 		printf("%s\n", (char *) tmp->content);
// 		tmp = tmp->next;
// 	}
// 	ft_lstclear(&mapped, del);
// 	while (lst)
// 	{
// 		tmp = lst;
// 		lst = lst->next;
// 		free(tmp);
// 	}
// }
