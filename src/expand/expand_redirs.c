/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:42:08 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 12:48:46 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Creates an empty string tracked by the line garbage collector.
1.	Used for quoted redirection targets that expand to an empty word
2.	Returns NULL if allocation or garbage collector registration fails
*/
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

/*
Reports an ambiguous redirect expansion error.
1.	Prints the original redirection word for a useful shell-style message
2.	Sets last_exit to 1 because redirection setup failed
*/
static int	ambiguous_redir(t_shell *shell, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	shell->last_exit = 1;
	return (0);
}

/*
Stores the single expanded word back into a redirection.
1.	Extracts word zero from the marked expansion result
2.	Replaces redir->file with the garbage-collected expanded word
*/
static int	set_redir_word(t_shell *shell, t_redir *redir, char *marked)
{
	char	*word;

	word = marked_get_word(shell, marked, 0);
	if (!word)
		return (0);
	redir->file = word;
	return (1);
}

/*
Expands a normal redirection target and checks ambiguity.
1.	Uses marked expansion so unquoted variables can split
2.	Rejects results that become more than one word
3.	Rejects empty unquoted results as ambiguous redirects
4.	Preserves quoted empty results as an empty filename
*/
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

/*
Expands every redirection target in a redirection list.
1.	Only removes quotes from heredoc delimiters
2.	Uses normal redirection expansion for all other redirection types
3.	Stops when expansion fails or creates an invalid target
*/
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
