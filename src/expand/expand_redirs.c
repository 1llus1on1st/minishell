/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:42:08 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/09 12:42:10 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*empty_gc_string(t_shell *shell)
{
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	if (!gc_add(&shell->line_gc, str))
		return (free(str), NULL);
	return (str);
}

static int	ambiguous_redir(t_shell *shell, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	shell->last_exit = 1;
	return (0);
}

static int	set_redir_word(t_shell *shell, t_redir *redir, char *marked)
{
	char	*word;

	word = marked_get_word(shell, marked, 0);
	if (!word)
		return (0);
	redir->file = word;
	return (1);
}

static int	expand_normal_redir(t_shell *shell, t_redir *redir)
{
	char	*marked;
	int		had_quote;
	int		count;

	marked = expand_marked_word(shell, redir->file, &had_quote);
	if (!marked)
		return (shell->last_exit = 1, 0);
	count = marked_word_count(marked);
	if (count > 1 || (count == 0 && !had_quote))
		return (ambiguous_redir(shell, redir->file));
	if (count == 0)
	{
		redir->file = empty_gc_string(shell);
		return (redir->file != NULL);
	}
	return (set_redir_word(shell, redir, marked));
}

int	expand_redirs(t_shell *shell, t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == T_HEREDOC)
			redirs->file = remove_quotes(shell, redirs->file);
		else if (!expand_normal_redir(shell, redirs))
			return (0);
		if (!redirs->file)
			return (shell->last_exit = 1, 0);
		redirs = redirs->next;
	}
	return (1);
}