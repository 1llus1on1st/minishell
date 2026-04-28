/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:51:36 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/28 12:52:44 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*gc_malloc(t_gc **gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!gc_add(gc, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

int	gc_add(t_gc **gc, void *ptr)
{
	t_gc	*node;

	node = malloc(sizeof(t_gc));
	if (!node)
		return (0);
	node->ptr = ptr;
	node->next = *gc;
	*gc = node;
	return (1);
}

void	gc_clear(t_gc **gc)
{
	t_gc	*current;
	t_gc	*next;

	current = *gc;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*gc = NULL;
}
