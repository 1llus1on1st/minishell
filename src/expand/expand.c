/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:28:02 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 19:58:47 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Expands every argument stored in one argv array.
1.	Starts from the first argument in argv
2.	Calls expand_string on each argument to handle quotes and variables
3.	Returns 0 if any argument expansion fails
4.	Replaces the old argv entry with the expanded string
5.	Returns 1 after all arguments have been expanded
*/
static int	expand_argv(t_shell *shell, char **argv)
{
	int		i;
	char	*expanded;

	i = 0;
	while (argv && argv[i])
	{
		expanded = expand_string(shell, argv[i]);
		if (!expanded)
			return (0);
		argv[i] = expanded;
		i++;
	}
	return (1);
}

/*
Expands every redirection filename in one command.
1.	Walks through the command redirection linked list
2.	Only removes quotes from heredoc delimiters
3.	Expands variables and removes quotes for normal redirection filenames
4.	Replaces the redirection file value with the expanded result
5.	Returns 0 if any expansion fails, otherwise returns 1
*/
static int	expand_redirs(t_shell *shell, t_redir *redirs)
{
	char	*expanded;

	while (redirs)
	{
		if (redirs->type == T_HEREDOC)
			expanded = remove_quotes(shell, redirs->file);
		else
			expanded = expand_string(shell, redirs->file);
		if (!expanded)
			return (0);
		redirs->file = expanded;
		redirs = redirs->next;
	}
	return (1);
}

/*
Expands arguments and redirections for every parsed command.
1.	Loops through the command linked list
2.	Expands the argv array of the current command
3.	Expands the redirection list of the current command
4.	Stops and returns 0 if any expansion step fails
5.	Returns 1 when every command has been expanded successfully
*/
int	expand(t_shell *shell, t_cmd *cmds)
{
	while (cmds)
	{
		if (!expand_argv(shell, cmds->argv))
			return (0);
		if (!expand_redirs(shell, cmds->redirs))
			return (0);
		cmds = cmds->next;
	}
	return (1);
}
