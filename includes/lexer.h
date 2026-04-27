/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:46:34 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/27 17:04:18 by mshargan         ###   ########.fr       */
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

t_token	*lexer(char *line);
void	skip_spaces(char *line, int *i);
t_token	*create_token(t_token_type type, char *value);
void	add_token_back(t_token **tokens, t_token *new_token);
void	handle_redir_in(char *line, int *i, t_token **tokens);
void	handle_redir_out(char *line, int *i, t_token **tokens);
void	handle_word(char *line, int *i, t_token **tokens);


#endif