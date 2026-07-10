/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:08:48 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 11:13:33 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_shell	t_shell;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				fd;
	int				heredoc_fd;
	int				heredoc_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*create_cmd(t_shell *shell);
int		add_arg(t_shell *shell, t_cmd *cmd, char *value);
void	add_cmd_back(t_cmd **cmds, t_cmd *new_cmd);
int		is_redir(t_token_type type);
int		parse_redir(t_shell *shell, t_token **token, t_cmd *cmd);
int		parser(t_shell *shell, t_token *tokens, t_cmd **cmds);
void	print_cmds(t_cmd *cmds);
int		check_syntax(t_token *tokens);
char	*token_value(t_token *token);

#endif
