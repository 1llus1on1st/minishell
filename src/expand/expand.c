/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:28:02 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 12:23:08 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static int	should_remove_empty_arg(char *original, char *expanded)
{
	if (!expanded || expanded[0] != '\0')
		return (0);
	if (has_quote(original))
		return (0);
	return (ft_strchr(original, '$') != NULL);
}

static int	expand_argv(t_shell *shell, char **argv)
{
	int		i;
	int		j;
	char	*original;
	char	*expanded;

	i = 0;
	j = 0;
	while (argv && argv[i])
	{
		original = argv[i];
		expanded = expand_string(shell, original);
		if (!expanded)
			return (0);
		if (!should_remove_empty_arg(original, expanded))
			argv[j++] = expanded;
		i++;
	}
	if (argv)
		argv[j] = NULL;
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
