/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 12:00:00 by mshargan          #+#    #+#             */
/*   Updated: 2026/05/18 12:00:00 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

t_cmd	*create_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = gc_malloc(&shell->line_gc, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	add_arg(t_shell *shell, t_cmd *cmd, char *value)
{
	char	**new_argv;
	int		i;

	i = count_args(cmd->argv);
	new_argv = gc_malloc(&shell->line_gc, sizeof(char *) * (i + 2));
	if (!new_argv)
		return (0);
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(value);
	if (!new_argv[i])
		return (0);
	if (!gc_add(&shell->line_gc, new_argv[i]))
		return (free(new_argv[i]), 0);
	new_argv[i + 1] = NULL;
	cmd->argv = new_argv;
	return (1);
}

void	add_cmd_back(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!*cmds)
	{
		*cmds = new_cmd;
		return ;
	}
	current = *cmds;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}


