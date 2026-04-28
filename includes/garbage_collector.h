/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:51:57 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/28 12:59:33 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

#include <stddef.h>

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}	t_gc;

void	*gc_malloc(t_gc **gc, size_t size);
int		gc_add(t_gc **gc, void *ptr);
void	gc_clear(t_gc **gc);

#endif