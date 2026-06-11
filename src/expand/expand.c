/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:28:02 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/11 11:28:42 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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