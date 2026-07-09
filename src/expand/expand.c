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

static int	expand_one_arg(t_shell *shell, t_cmd *cmd, char *arg)
{
	char	*marked;
	int		had_quote;

	marked = expand_marked_word(shell, arg, &had_quote);
	if (!marked)
		return (0);
	return (add_marked_words(shell, cmd, marked, had_quote));
}

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
