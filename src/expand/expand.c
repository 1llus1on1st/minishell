/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:28:02 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 12:41:49 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Expands one argv word and adds the resulting field(s) back to the command.
1.	Uses marked expansion so unquoted variables can still split into words
2.	Keeps track of quotes because quoted empty strings must be preserved
3.	Adds zero, one or many argv entries depending on the expanded result
*/
static int	expand_one_arg(t_shell *shell, t_cmd *cmd, char *arg)
{
	char	*marked;
	int		had_quote;

	marked = expand_marked_word(shell, arg, &had_quote);
	if (!marked)
		return (0);
	return (add_marked_words(shell, cmd, marked, had_quote));
}

/*
Rebuilds a command argv array after expansion.
1.	Saves the old argv pointer before resetting cmd->argv
2.	Expands each original argument independently
3.	Allows one original word to become multiple argv entries after splitting
*/
static int	expand_argv(t_shell *shell, t_cmd *cmd)
{
	char	**old_argv;
	int		i;

	old_argv = cmd->argv;
	cmd->argv = NULL;
	i = 0;
	while (old_argv && old_argv[i])
	{
		if (!expand_one_arg(shell, cmd, old_argv[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
Runs expansion for every parsed command.
1.	Expands argv before redirections because they have different rules
2.	Expands redirection targets and detects ambiguous redirects
3.	Stops at the first expansion failure and preserves the exit status
*/
int	expand(t_shell *shell, t_cmd *cmds)
{
	while (cmds)
	{
		if (!expand_argv(shell, cmds))
			return (shell->last_exit = 1, 0);
		if (!expand_redirs(shell, cmds->redirs))
			return (0);
		cmds = cmds->next;
	}
	return (1);
}
