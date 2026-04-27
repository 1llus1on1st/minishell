/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:46:34 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/27 17:37:49 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

int		lexer(char *line, t_token **tokens);
void	skip_spaces(char *line, int *i);
t_token	*create_token(t_token_type type, char *value);
int		add_token_back(t_token **tokens, t_token *new_token);
int		handle_redir_in(char *line, int *i, t_token **tokens);
int		handle_redir_out(char *line, int *i, t_token **tokens);
int		handle_word(char *line, int *i, t_token **tokens);


#endif