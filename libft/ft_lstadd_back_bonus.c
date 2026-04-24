/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:13:14 by mshargan          #+#    #+#             */
/*   Updated: 2025/11/18 18:49:18 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*res;

	if (!lst)
		return ;
	res = *lst;
	if (!res)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	while (res->next)
	{
		res = res->next;
	}
	res->next = new;
}
