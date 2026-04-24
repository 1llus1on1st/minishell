/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:13:41 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/24 15:07:23 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*first_protection(void **first_content, void (*del)(void *))
{
	(*del)(*first_content);
	return (NULL);
}

static t_list	*second_protection(t_list **first, void (*del)(void *))
{
	ft_lstclear(first, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*current;
	void	*first_content;

	if (!lst || !f || !del)
		return (NULL);
	first_content = (*f)(lst->content);
	current = ft_lstnew(first_content);
	if (!current)
		return (first_protection(&first_content, del));
	first = current;
	while (lst->next)
	{
		lst = lst->next;
		current->next = malloc(sizeof(t_list));
		if (!(current->next))
			return (second_protection(&first, del));
		current = current->next;
		current->content = (*f)(lst->content);
		current->next = NULL;
	}
	return (first);
}
