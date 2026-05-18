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

static void	print_redirs(t_redir *redirs)
{
	while (redirs)
	{
		printf("  redir: %s %s\n", redir_type_to_str(redirs->type),
			redirs->file);
		redirs = redirs->next;
	}
}

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
