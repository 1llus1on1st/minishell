/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 12:00:00 by mshargan          #+#    #+#             */
/*   Updated: 2026/05/18 12:00:00 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Converts a redirection token type into a printable debug string.
1.	Checks for input redirection and returns "REDIR_IN"
2.	Checks for output redirection and returns "REDIR_OUT"
3.	Checks for append redirection and returns "APPEND"
4.	Checks for heredoc redirection and returns "HEREDOC"
5.	Returns "UNKNOWN" for any type that is not a redirection type
*/
static char	*redir_type_to_str(t_token_type type)
{
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_APPEND)
		return ("APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

/*
Prints all redirections attached to one command for debugging.
1.	Loops through the redirection linked list
2.	Converts each redirection type into a readable string
3.	Prints the redirection type and file value
4.	Moves to the next redirection until the list ends
*/
static void	print_redirs(t_redir *redirs)
{
	while (redirs)
	{
		printf("  redir: %s %s\n", redir_type_to_str(redirs->type),
			redirs->file);
		redirs = redirs->next;
	}
}

/*
Prints the parsed command list for debugging.
1.	Loops through every command in the command linked list
2.	Prints a command number before each command
3.	Prints every argv entry stored in the command
4.	Prints every redirection attached to the command
5.	Moves to the next command until the list ends
*/
void	print_cmds(t_cmd *cmds)
{
	int	i;
	int	cmd_n;

	cmd_n = 1;
	while (cmds)
	{
		printf("cmd %d:\n", cmd_n++);
		i = 0;
		while (cmds->argv && cmds->argv[i])
		{
			printf("  argv[%d]: %s\n", i, cmds->argv[i]);
			i++;
		}
		print_redirs(cmds->redirs);
		cmds = cmds->next;
	}
}
