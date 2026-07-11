/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 17:55:28 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:22:01 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Exits a child process after cleaning inherited shell allocations.
1.	Clears line-level allocations copied into the child by fork
2.	Clears shell-level allocations before exiting the child
3.	Exits with the status chosen by the child execution path
*/
void	exit_child(t_shell *shell, int status)
{
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	exit(status);
}
