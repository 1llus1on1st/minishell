/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:34:34 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:32:00 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# ifndef EXP_SPLIT
#  define EXP_SPLIT 31
# endif

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

int		expand(t_shell *shell, t_cmd *cmds);
int		expand_redirs(t_shell *shell, t_redir *redirs);
char	*expand_marked_word(t_shell *shell, char *str, int *had_quote);
int		handle_marked_char(t_shell *shell, char *str, char **res, int *i);
int		expand_unquoted_variable(t_shell *shell, char *str, char **res, int *i);
int		expand_quoted_variable(t_shell *shell, char *str, char **res, int *i);
int		marked_word_count(char *str);
char	*marked_get_word(t_shell *shell, char *str, int index);
int		add_marked_words(t_shell *shell, t_cmd *cmd, char *marked,
			int keep_empty);
char	*expand_string(t_shell *shell, char *str);
char	*remove_quotes(t_shell *shell, char *str);
int		append_char(t_shell *shell, char **res, char c);
int		append_str(t_shell *shell, char **res, char *str);
int		expand_variable(t_shell *shell, char *str, char **res, int *i);
char	*expand_heredoc_line(t_shell *shell, char *str);
int		is_var_char(char c);

#endif