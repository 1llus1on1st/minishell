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

/*
Counts how many arguments are currently stored in an argv array.
1.	Starts counting from index 0
2.	Checks that argv exists before reading from it
3.	Moves through the array until it reaches the NULL terminator
4.	Returns the number of argument strings found
*/
static int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

/*
Creates and initializes a new command structure.
1.	Allocates memory for a t_cmd using the line garbage collector
2.	Sets argv to NULL because no arguments have been added yet
3.	Sets redirs to NULL because no redirections have been added yet
4.	Sets next to NULL so the command can safely become the end of a list
5.	Returns the new command or NULL if allocation fails
*/
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

/*
Adds one argument string to a command argv array.
1.	Counts the existing arguments in cmd->argv
2.	Allocates a larger argv array with space for the new argument and NULL
3.	Copies the old argument pointers into the new array
4.	Duplicates the new value and stores it in the new array
5.	Adds the duplicated string to the garbage collector and updates cmd->argv
*/
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

/*
Adds a command to the end of the command linked list.
1.	If the command list is empty, stores the new command as the first command
2.	Otherwise starts from the first command in the list
3.	Moves forward until it reaches the last command
4.	Links the last command to the new command
*/
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
