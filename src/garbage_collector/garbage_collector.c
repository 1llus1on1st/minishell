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

/*
Allocates memory and immediately registers it in a garbage collector list.
1.	Calls malloc with the requested size
2.	Returns NULL if the allocation fails
3.	Adds the allocated pointer to the selected garbage collector list
4.	Frees the pointer and returns NULL if registration fails
5.	Returns the allocated pointer when both allocation and registration succeed
*/
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

/*
Adds an existing pointer to a garbage collector list.
1.	Allocates a new garbage collector node
2.	Returns 0 if the node allocation fails
3.	Stores the tracked pointer inside the new node
4.	Places the new node at the beginning of the garbage collector list
5.	Returns 1 when the pointer is successfully registered
*/
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

/*
Frees every pointer stored in a garbage collector list.
1.	Starts from the first node in the garbage collector list
2.	Saves the next node before freeing the current one
3.	Frees the tracked pointer stored in the current node
4.	Frees the garbage collector node itself
5.	Sets the list pointer to NULL after everything has been cleared
*/
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
