/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 12:00:00 by mshargan          #+#    #+#             */
/*   Updated: 2026/05/18 12:00:00 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether the current command has no arguments or redirections.
1.	Looks at the argv field to see if any command arguments were added
2.	Looks at the redirs field to see if any redirections were added
3.	Returns 1 when both fields are empty
4.	Returns 0 when the command contains arguments or redirections
*/
static int	cmd_is_empty(t_cmd *cmd)
{
	if (!cmd->argv && !cmd->redirs)
		return (1);
	return (0);
}

/*
Handles a pipe token by finishing the current command.
1.	Rejects the pipe if the current command is empty
2.	Adds the completed command to the command list
3.	Creates a new empty command for the tokens after the pipe
4.	Returns 0 if command creation fails
5.	Returns 1 when the parser is ready to continue after the pipe
*/
static int	parse_pipe(t_shell *shell, t_cmd **cmds, t_cmd **cmd)
{
	if (cmd_is_empty(*cmd))
		return (0);
	add_cmd_back(cmds, *cmd);
	*cmd = create_cmd(shell);
	if (!*cmd)
		return (0);
	return (1);
}

/*
Parses one token and sends it to the correct parser helper.
1.	Adds word tokens to the current command as arguments
2.	Parses redirection tokens with their following filename token
3.	Handles pipe tokens by closing the current command
4.	Passes token and command pointers so helpers can advance or replace them
5.	Returns 0 if the token cannot be parsed correctly
*/
static int	parse_token(t_shell *shell, t_token **token, t_cmd **cmds,
	t_cmd **cmd)
{
	if ((*token)->type == T_WORD)
		return (add_arg(shell, *cmd, (*token)->value));
	if (is_redir((*token)->type))
		return (parse_redir(shell, token, *cmd));
	if ((*token)->type == T_PIPE)
		return (parse_pipe(shell, cmds, cmd));
	return (0);
}

/*
Builds a command list from the token list created by the lexer.
1.	Checks the full token list for syntax errors before parsing
2.	Creates the first empty command structure
3.	Loops through each token and parses it into commands, args or redirs
4.	Adds the final command to the command list when it is not empty
5.	Returns 0 on success and 1 if syntax, allocation or parsing fails
*/
int	parser(t_shell *shell, t_token *tokens, t_cmd **cmds)
{
	t_cmd	*cmd;

	if (!check_syntax(tokens))
		return (1);
	cmd = create_cmd(shell);
	if (!cmd)
		return (1);
	while (tokens)
	{
		if (!parse_token(shell, &tokens, cmds, &cmd))
			return (1);
		tokens = tokens->next;
	}
	if (cmd_is_empty(cmd))
		return (*cmds != NULL);
	add_cmd_back(cmds, cmd);
	return (0);
}
