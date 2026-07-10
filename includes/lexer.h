/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:19 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:29:33 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_shell	t_shell;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_READ_WRITE,
	T_HERE_STRING
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

int		lexer(t_shell *shell, char *line, t_token **tokens);
t_token	*create_token(t_shell *shell, t_token_type type, char *value);
int		add_token_back(t_token **tokens, t_token *new_token);
int		handle_pipe(t_shell *shell, int *i, t_token **tokens);
int		add_redir_token(t_shell *shell, t_token **tokens,
			char *value, t_token_type type);
void	get_input_redir(char *line, int op, t_token_type *type);
int		get_input_len(char *line, int start, int op);
int		get_output_len(char *line, int start, int op,
			t_token_type *type);
int		handle_redir_in(t_shell *shell, char *line, int *i, t_token **tokens);
int		handle_redir_out(t_shell *shell, char *line, int *i, t_token **tokens);
int		handle_word(t_shell *shell, char *line, int *i, t_token **tokens);

#endif